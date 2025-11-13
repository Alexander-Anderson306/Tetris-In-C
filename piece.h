#ifndef PIECE_H
#define PIECE_H

#define PIECE_COMPONENT '#'
//when a line gets filled in, the line will flash with DELETING_COMPONENT once then it gets deleted
#define DELETING_COMPONENT '@'

enum PieceType {
    LINE,
    SQUARE,
    L,
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
    int x;
    int y;
    enum PieceType type;
} Piece_Component;

typedef struct Piece {
    Piece_Component components[4];
} Piece;

void init_piece(Piece* piece);
void rotate_piece(Piece* piece);

#endif