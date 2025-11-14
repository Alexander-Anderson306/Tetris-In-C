#include "game.h"

int main() {
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
            //move the piece down 
            move_down(&piece_copy);
            //check if the piece is valid
            not_moving = update_board(&board_copy, &piece_copy, &piece);
            //if the piece is valid then update the board
            if(not_moving != 2) {
                *board = board_copy;
                piece = piece_copy;
            }
            //print the board
            print_board(board);
        } while(!not_moving);

        //check if the top row has an object
        for(int i = 0; i < COLS; i++) {
            if(board->character_board[1][i] != EMPTY_SPACE) {
                flag = 0;
            }
        }
    }
}