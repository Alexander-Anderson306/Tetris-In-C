#include "game.h"
int gravity_tick_rates[] = {1000000, 800000, 600000, 400000, 200000, 100000};

_Atomic char game_over = 0;
//this mutex will be used to lock access to the board
static pthread_mutex_t board_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    //seed random
    srand(time(NULL));
    //set raw mode
    set_raw_mode();
    Board board;
    init_board(&board);
    Piece piece;
    init_piece(&piece);
    //put the piece on the board and start the game loop
    update_board(&board, &piece, NULL);
    print_board(&board);
    printf("Score: %d\n", 0);
    int score = 0;
    game_loop(&board, &piece, &score);
    reset_terminal();
    //print the final score
    printf("Final Score: %d\n", score);
    return 0;
}

void game_loop(Board* board, Piece* piece, int* score) {
    int gravity_index = 0;
    char result = 0;
    Board copy;
    while(!game_over) {
        usleep(gravity_tick_rates[gravity_index]);

        pthread_mutex_lock(&board_mutex);

        //save a copy of the last piece for proper update
        Piece temp;
        copy_piece(piece, &temp);

        //move the piece down
        gravity_tick(piece);

        //update the board
        result = update_board(board, piece, &temp);

        //if the result is one we need a new piece
        if(result == 1) {
            init_piece(piece);
        } else if(result == 2) {
            game_over = 1;
        }

        //check for clears
        score = check_for_clears_and_score(board, gravity_tick_rates[gravity_index]);

        //take a copy of the board for printing
        copy_board(board, &copy);
        //unlock access to the board
        pthread_mutex_unlock(&board_mutex);

        pthread_mutex_lock(&print_mutex);
        print_board(&copy);
        printf("Score: %d\n", score);
        pthread_mutex_unlock(&print_mutex);
        gravity_index = update_fall_tick_rate(score);
    }
}


/**
 * This function is a thread that is responsible for handling user input.
 * It takes two arguments, a pointer to a Board and a pointer to a Piece.
 * It will continuously read user input and update the board accordingly.
 * If the user presses 'q', the game_over variable will be set to 1 and the thread will exit.
 * If the user presses a valid movement key (left, right, down), the thread will update the board accordingly.
 * If the user presses a valid rotation key (left or right), the thread will update the piece accordingly.
 * If the update is invalid, the thread will do nothing.
 * If the update is valid, but the piece needs a new piece, the thread will set the need_new_piece variable to 1.
 */
void* input_thread(void* args) {
    //the argument is the board and the current piece we are working with
    Thread_Args* thread_args = (Thread_Args*) args;
    Board* board = thread_args->board;
    Piece* piece = thread_args->piece;
    int* score = thread_args->score;
    char input;

    while(!game_over) {
        usleep(USER_TICK_RATE);

        if (read(STDIN_FILENO, &input, 1) > 0) {

            pthread_mutex_lock(&board_mutex);

            //save temp copies to validate input before committing
            Piece temp_piece;
            copy_piece(piece, &temp_piece);

            Board temp_board;
            copy_board(board, &temp_board);

            if (input == QUIT) {
                game_over = 1;
                pthread_mutex_unlock(&board_mutex);
                return NULL;
            }

            //apply movement/rotation to temp_piece first
            if (input == ROTATE_LEFT || input == ROTATE_RIGHT) {
                rotate_piece(&temp_piece, input);
            } 
            else if (input == LEFT || input == RIGHT || input == DROP) {
                move_piece(&temp_piece, board, input);
            }

            //test the update on temp state
            char result = update_board(&temp_board, &temp_piece, piece);

            if (result == 0 || result == 1) {
                //valid update commit piece and board
                copy_piece(&temp_piece, piece);
                copy_board(&temp_board, board);
            }
            //else: invalid (result == 2) do nothing (old piece and board remain)
            Board copy;
            copy_board(board, &copy);
            pthread_mutex_unlock(&board_mutex);

            pthread_mutex_lock(&print_mutex);
            print_board(&copy);
            printf("Score: %d\n", *score);
            pthread_mutex_unlock(&print_mutex);
        }
    }

    return NULL;
}

int check_for_clears_and_score(Board* board, int tick_rate) {
    //NOTE: we do rows and cols 1 to length-1 because we dont need to worry about the rim of the board

    char rows[ROWS];
    //find row indexs of rows we need to clear
    //tally up the score as well
    int score = 0;
    int num_cleared_in_a_row = 0;
    for(int i = 1; i < ROWS-1; i++) {
        char clear_flag = 1;
        for(int j = 1; j < COLS-1; j++) {
            if(board->character_board[i][j] == EMPTY_SPACE) {
                clear_flag = 0;
                break;
            }
        }

        if(clear_flag) {
            rows[i] = 1;
            ++num_cleared_in_a_row;
            //get the right score
            switch(num_cleared_in_a_row) {
                case 1:
                    score += 100;
                    break;
                case 2:
                    score += 250;
                    break;
                case 3:
                    score += 500;
                    break;
                case 4:
                    score += 1000;
                    break;
                //just in case shenanigans occur
                default:
                    score += 100;
                    break;
            }
        } else {
            rows[i] = 0;
            num_cleared_in_a_row = 0;
        }
    }

    //we can return early if there are no clears
    if(!score) {
        return score;
    }

    //make a copy of the board with the flashed rows state
    Board flashed_board;
    copy_board(board, &flashed_board);

    RGB grey = get_color((enum Piece_Type) -1);
    //fill the filled rows with flashing characters
    for(int i = 1; i < ROWS-1; i++) {
        if(rows[i]) {
            for(int j = 1; j < COLS-1; j++) {
                flashed_board.character_board[i][j] = FLASHING_COMPONENT;
                flashed_board.color_board[i][j].r = grey.r;
                flashed_board.color_board[i][j].g = grey.g;
                flashed_board.color_board[i][j].b = grey.b;
            }
        }
    }

    //now clear the rows (flash them 3 times then remove them)
    int num_flashes = 0;
    while(num_flashes < 3){
        //flash the pieces that are getting deleted
        print_board(board);
        usleep(tick_rate/4);
        print_board(&flashed_board);
        ++num_flashes;
        usleep(tick_rate/4);
    }

    //remove the cleared rows and update the board
    for(int i = 1; i < ROWS-1; i++) {
        if(rows[i]) {
            for(int j = 1; j < COLS-1; j++) {
                board->character_board[i][j] = EMPTY_SPACE;
                board->color_board[i][j].r = grey.r;
                board->color_board[i][j].g = grey.g;
                board->color_board[i][j].b = grey.b;
            }
        }
    }

    //print the cleared board to show the deletion
    print_board(board);
    usleep(tick_rate/4);

    //update the board (move all the pieces that can move down down)
    for(int i = ROWS-1; i > 1; i--) {
        for(int j = 1; j < COLS-1; j++) {
            //move the piece down until it hits something
            int new_row = i;
            while(new_row > 1 && board->character_board[new_row-1][j] == EMPTY_SPACE) --new_row;
            //move the piece if we have to
            if(new_row != i) {
                RGB color;
                copy_rgb(&board->color_board[i][j], &color);
                board->character_board[new_row][j] = PIECE_COMPONENT;
                board->color_board[new_row][j].r = color.r;
                board->color_board[new_row][j].g = color.g;
                board->color_board[new_row][j].b = color.b;
                board->character_board[i][j] = EMPTY_SPACE;
                board->color_board[i][j].r = grey.r;
                board->color_board[i][j].g = grey.g;
                board->color_board[i][j].b = grey.b;
            }
        }
    }

    //print the new board
    print_board(board);
    //all done return the score
    return score;
}

/**
 * Returns the index of the gravity tick rate array based on the current score.
 *
 * The fall tick rate determines how often the piece should fall down one row.
 * The higher the score, the faster the piece should fall.
 *
 *
 * @param score The current score.
 * @return The updated fall tick rate.
 */
int update_fall_tick_rate(int score) {
    if(score < 1000) {
        return 0;
    } else if(score < 2500) {
        return 1;
    } else if(score < 6000) {
        return 2;
    } else if(score < 10000) {
        return 3;
    } else if(score < 20000) {
        return 4;
    } else {
        return 5;
    }
}