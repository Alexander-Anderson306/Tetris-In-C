#include "game.h"
int gravity_tick_rates[] = {1000000, 800000, 600000, 400000, 200000, 100000};

char game_over = 0;
//this mutex will be used to lock access to the board
static pthread_mutex_t board_mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    //seed random
    srand(time(NULL));
    //set raw mode
    set_raw_mode();
    Board board;
    init_board(&board);
    game_loop(&board);
    reset_terminal();
    return 0;
}

void game_loop(Board* board) {
    //
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
        usleep(tick_rate/3);
        print_board(&flashed_board);
        ++num_flashes;
        usleep(tick_rate/3);
    }

    //remove the cleared rows and update the board
    for(int i = 0; i < ROWS; i++) {
        if(rows[i]) {
            for(int j = 1; j < COLS-1; j++) {
                board->character_board[i][j] = EMPTY_SPACE;
                board->color_board[i][j].r = grey.r;
                board->color_board[i][j].g = grey.g;
                board->color_board[i][j].b = grey.b;
            }
        }
    }

    //update the board (move all the pieces that can move down down)
    //this logic broke the pieces will end up floating gotta fix it
    for(int i = ROWS-1; i > 1; i--) {
        for(int j = 1; j < COLS-1; j++) {
            //move the piece down one if it can
            if(board->character_board[i][j] != EMPTY_SPACE && board->character_board[i-1][j] == EMPTY_SPACE) {
                RGB color;
                copy_rgb(&board->color_board[i][j], &color);
                board->character_board[i-1][j] = board->character_board[i][j];
                board->color_board[i-1][j].r = color.r;
                board->color_board[i-1][j].g = color.g;
                board->color_board[i-1][j].b = color.b;
                board->character_board[i][j] = EMPTY_SPACE;
                board->color_board[i][j].r = grey.r;
                board->color_board[i][j].g = grey.g;
                board->color_board[i][j].b = grey.b;
            }
        }
    }

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
    if(score < 500) {
        return 0;
    } else if(score < 2500) {
        return 1;
    } else if(score < 4000) {
        return 2;
    } else if(score < 8000) {
        return 3;
    } else if(score < 10000) {
        return 4;
    } else {
        return 5;
    }
}