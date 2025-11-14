#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include <stdlib.h>

#define PIECE_COMPONENT '#'
//when a line gets filled in, the line will flash with DELETING_COMPONENT once then it gets deleted
#define DELETING_COMPONENT '@'

#define START_ROW 1
#define START_COL 10

enum PieceType {
    LINE,
    SQUARE,
    L,
    REVERS_L,
    Z,
    REVERS_Z,
    T
};

enum ButtonPress {
    SPEEDUP = 's',
    LEFT = 'a',
    RIGHT = 'd',
    ROTATE_LEFT = 'q',
    ROTATE_RIGHT = 'e',
    //ESC = 27
    QUIT = 27
};

typedef struct Piece_Component {
    int row;
    int col;
    int x;
    int y;
} Piece_Component;

typedef struct Piece {
    Piece_Component components[4];
    enum PieceType type;
} Piece;

void init_piece(Piece* piece);
void copy_piece(Piece* source, Piece* destination);
void rotate_piece(Piece* piece, char direction);

#endif