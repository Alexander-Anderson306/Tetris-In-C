#include "board.h"

/**
 * Initializes a given board with the appropriate characters.
 *
 * @param board The board to be initialized.
 */
void init_board(Board* board) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || i == ROWS - 1) {
                board->character_board[i][j] = TOP_BOTTEM_EDGE;
                board->color_board[i][j].r = 0;
                board->color_board[i][j].g = 0;
                board->color_board[i][j].b = 0;
            } else if(j == 0 || j == COLS - 1) {
                board->character_board[i][j] = LEFT_RIGHT_EDGE;
                board->color_board[i][j].r = 0;
                board->color_board[i][j].g = 0;
                board->color_board[i][j].b = 0;
            } else {
                //may have to change this depending on how blank spaces get printed
                board->character_board[i][j] = EMPTY_SPACE;
                board->color_board[i][j].r = 0;
                board->color_board[i][j].g = 0;
                board->color_board[i][j].b = 0;
            }
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
void print_board(Board board) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            //we print the piece and its current color
            printf("\x1b[38;2%d;%d;%dm%c", board.color_board[i][j].r, board.color_board[i][j].g, board.color_board[i][j].b, 
                board.character_board[i][j]);
        }
    }
}