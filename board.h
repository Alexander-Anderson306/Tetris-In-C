#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <string.h>
#include "piece.h"

#define ROWS 22
#define COLS 12
#define TOP_BOTTEM_EDGE '-'
#define LEFT_RIGHT_EDGE '|'
#define EMPTY_SPACE ' '

typedef struct RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct Board {
    char character_board[ROWS][COLS];
    RGB color_board[ROWS][COLS];
} Board;

void init_board(Board* board);
void print_board(Board* board);
void copy_board(Board* source, Board* destination);
RGB get_color(enum PieceType type);
char update_board(Board* board, Piece* new_piece, Piece* old_piece);

#endif