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
        //generate a new piece
        Piece piece;
        init_piece(&piece);
        //while the piece is moving
        char not_moving = 0;
        do {
            //sleep first
            sleep(1);
            //get a copy of the current board and piece for update and movement validation
            Board board_copy;
            copy_board(board, &board_copy);
            Piece piece_copy;
            copy_piece(&piece, &piece_copy);
            not_moving = update_board(&board_copy, &piece_copy, &piece);
            //if the piece is valid then update the board
            if(not_moving != 2) {
                *board = board_copy;
                piece = piece_copy;
            }
            //print the board
            print_board(board);
            //move the piece down
            move_piece(&piece, 's');
            //check if the piece is valid
        } while(!not_moving);

        //check if the top row has an object
        for(int i = 1; i < COLS-1; i++) {
            if(board->character_board[1][i] != EMPTY_SPACE) {
                flag = 0;
            }
        }
    }
}