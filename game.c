#include "game.h"

int main() {
    //seed random
    srand(time(NULL));
    Board board;
    init_board(&board);
    game_loop(&board);
    return 0;
}

void game_loop(Board* board) {
    //handle user input later just testing for now
    char flag = 1;
    print_board(board);
    while(flag) {
        //check if the top row has a piece component
        for(int i = 1; i < COLS-1; i++) {
            if(board->character_board[1][i] != EMPTY_SPACE) {
                flag = 0;
            }
        }

        //generate a new piece
        Piece piece;
        init_piece(&piece);
        //put the piece in the board
        update_board(board, &piece, NULL);
        //while the piece is moving
        char not_moving = 0;
        do {
            //half a second
            usleep(500000);
            //copy the piece just in case the movement is invalid and copy board just in case the movement is invalid
            Piece old_piece;
            Board old_board;
            copy_board(board, &old_board);
            copy_piece(&piece, &old_piece);
            //move the piece down
            move_piece(&piece, 's');
            //update the board
            not_moving = update_board(board, &piece, &old_piece);
            //check if the movement was valid
            if(not_moving == 2) {
                //movement invalid use the old board
                *board = old_board;
                piece = old_piece;
            }

            print_board(board);
        } while(!not_moving);
    }
}