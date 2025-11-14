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

//this function will likely need its own thread
void check_for_clears_and_score(Board* board) {
    //check for clears and return the score of the clear
    //also update the board

    char rows[ROWS];
    memset(rows, 0, ROWS);

    while(!game_over) {
        usleep(USER_TICK_RATE);
        //find row indexs of rows we need to clear
        for(int i = 0; i < ROWS; i++) {
            char clear_flag = 1;
            for(int j = 0; j < COLS; j++) {
                if(board->character_board[i][j] == EMPTY_SPACE) {
                    clear_flag = 0;
                    break;
                }
            }

            if(clear_flag) {
                rows[i] = 1;
            }
        }

        //now clear the rows
        //keep track of the number of clears for the score
    }
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