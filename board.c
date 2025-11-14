#include "board.h"

/**
 * Initializes a given board with the appropriate characters.
 *
 * @param board The board to be initialized.
 */
void init_board(Board* board) {
    //initialize top and bottom row
    for(int i = 0; i < COLS; i++) {
        board->character_board[0][i] = TOP_BOTTEM_EDGE;
        board->character_board[ROWS - 1][i] = TOP_BOTTEM_EDGE;
        board->color_board[0][i].r = 0;
        board->color_board[0][i].g = 0;
        board->color_board[0][i].b = 0;
        board->color_board[ROWS - 1][i].r = 0;
        board->color_board[ROWS - 1][i].g = 0;
        board->color_board[ROWS - 1][i].b = 0;
    }

    //initialize the rest of the board
    for(int i = 1; i < ROWS-1; i++) {
        for(int j = 0; j < COLS; j++) {
            if(j == 0 || j == COLS - 1) {
                board->character_board[i][j] = LEFT_RIGHT_EDGE;
            } else {
                board->character_board[i][j] = EMPTY_SPACE;
            }
            board->color_board[i][j].r = 0;
            board->color_board[i][j].g = 0;
            board->color_board[i][j].b = 0;
        }
    }
}

/**
 * Prints a given board to the console.
 *
 * This function prints the character_board to the console, using ANSI escape
 * codes to set the color of each character to the corresponding color in the
 * color_board. The board is printed row by row, with each row on a new line.
 *
 * @param board The board to be printed.
 */
void print_board(Board* board) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            //we print the piece and its current color
            printf("\x1b[38;2%d;%d;%dm%c", board->color_board[i][j].r, board->color_board[i][j].g, board->color_board[i][j].b, board->character_board[i][j]);
            //add a space after each character for better readability
            printf(" ");
        }
        printf("\n");
    }
}

/**
 * Copies the character_board and color_board of a given source board to a given destination board.
 * 
 *
 * @param source The board to copy from.
 * @param destination The board to copy to.
 */
void copy_board(Board* source, Board* destination) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            destination->character_board[i][j] = source->character_board[i][j];
            destination->color_board[i][j].r = source->color_board[i][j].r;
            destination->color_board[i][j].g = source->color_board[i][j].g;
            destination->color_board[i][j].b = source->color_board[i][j].b;
        }
    }
}

RGB get_color(enum PieceType type) {
    switch (type) {
        case LINE:
            return (RGB){3, 248, 252};
        case SQUARE:
            return (RGB){244, 252, 3};
        case L:
            return (RGB){252, 190, 3};
        case REVERS_L:
            return (RGB){232, 90, 237};
        case Z:
            return (RGB){86, 252, 3};
        case REVERS_Z:
            return (RGB){252, 19, 3};
        case T:
            return (RGB){128, 0, 255};
    }
}

/**
 * Updates a given board by removing an old piece and adding a new piece.
 *
 *
 * @param board The board to be updated.
 * @param new_piece The new piece to be added to the board.
 * @param old_piece The old piece to be removed from the board.
 * @return 1 if the piece is valid but cannot move down any further, 2 if the piece is invalid.
 */
char update_board(Board* board, Piece* new_piece, Piece* old_piece) {
    //get rid of the old piece
    if(old_piece != NULL){
        for(int i = 0; i < 4; i++) {
            board->character_board[old_piece->components[i].row][old_piece->components[i].col] = EMPTY_SPACE;
            board->color_board[old_piece->components[i].row][old_piece->components[i].col].r = 0;
            board->color_board[old_piece->components[i].row][old_piece->components[i].col].g = 0;
            board->color_board[old_piece->components[i].row][old_piece->components[i].col].b = 0;
        }
    }

    //color of the piece
    RGB color = get_color(new_piece->type);
    //add new peice
    //return 1 if piece is valid, but cannot move down any further
    //return 2 if the piece is invalid
    for(int i = 0; i < 4; i++) {
        if(board->character_board[new_piece->components[i].row][new_piece->components[i].col] == EMPTY_SPACE) {
            board->character_board[new_piece->components[i].row][new_piece->components[i].col] = PIECE_COMPONENT;
            board->color_board[new_piece->components[i].row][new_piece->components[i].col].r = color.r;
            board->color_board[new_piece->components[i].row][new_piece->components[i].col].g = color.g;
            board->color_board[new_piece->components[i].row][new_piece->components[i].col].b = color.b;
        } else {
            return 2;
        }
    }

    //now check if the piece can move down again
    for(int i = 0; i < 4; i++) {
        if(board->character_board[new_piece->components[i].row + 1][new_piece->components[i].col] != EMPTY_SPACE) {
            //check if this piece component is part of the current piece
            char cant_fall = 1;
            for(int j = 0; j < 4; j++) {
                if(new_piece->components[i].col == new_piece->components[j].col && new_piece->components[i].row == new_piece->components[j].row) {
                    //the piece component is just part of the current piece (no problem keep falling)
                    cant_fall = 0;
                }
            }

            if(cant_fall) {
                return 1;
            }
        }
    }

    return 0;
}