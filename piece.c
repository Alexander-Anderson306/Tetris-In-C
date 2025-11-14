#include "piece.h"

//keep left rotation and right rotation constantly loaded in memory and just use references to them
//Flatened 2X2 matrix: 0 = 00, 1 = 01, 2 = 10, 3 = 11
int left_rotation[] = {0, -1, 1, 0};
int right_rotation[] = {0, 1, -1, 0};

/**
 * Initializes a given piece with a random piece type and corresponding components.
 *
 * The generated piece will have a random piece type, and the corresponding components
 * will be set according to the piece type.
 *
 * @param piece The piece to be initialized.
 */
void init_piece(Piece* piece) {
    //generate random piece type
    enum PieceType type = (enum PieceType) rand() % 7;
    piece->type = type;

    //may need to fix stuff later here
    switch(type) {
        case LINE:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL - 1;
            piece->components[0].x = -1;
            piece->components[0].y = 0;
            //second component rotate around this one
            piece->components[1].row = START_ROW;
            piece->components[1].col = START_COL;
            piece->components[1].x = 0;
            piece->components[1].y = 0;
            //third component
            piece->components[2].row = START_ROW;
            piece->components[2].col = START_COL + 1;
            piece->components[2].x = 1;
            piece->components[2].y = 0;
            //fourth component
            piece->components[3].row = START_ROW;
            piece->components[3].col = START_COL + 2;
            piece->components[3].x = 2;
            piece->components[3].y = 0;
            break;
        case SQUARE:
            //first component rotate around this one
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL;
            piece->components[0].x = 0;
            piece->components[0].y = 0;
            //second component
            piece->components[1].row = START_ROW;
            piece->components[1].col = START_COL + 1;
            piece->components[1].x = 1;
            piece->components[1].y = 0;
            //third component
            piece->components[2].row = START_ROW + 1;
            piece->components[2].col = START_COL;
            piece->components[2].x = 0;
            piece->components[2].y = -1;
            //fourth component
            piece->components[3].row = START_ROW + 1;
            piece->components[3].col = START_COL + 1;
            piece->components[3].x = 1;
            piece->components[3].y = -1;
            break;
        case L:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL;
            piece->components[0].x = 0;
            piece->components[0].y = 0;
            //second component
            piece->components[1].row = START_ROW + 1;
            piece->components[1].col = START_COL;
            piece->components[1].x = 0;
            piece->components[1].y = -1;
            //third component rotate around this one
            piece->components[2].row = START_ROW + 2;
            piece->components[2].col = START_COL;
            piece->components[2].x = 0;
            piece->components[2].y = -2;
            //fourth component
            piece->components[3].row = START_ROW + 2;
            piece->components[3].col = START_COL + 1;
            piece->components[3].x = 1;
            piece->components[3].y = -2;
            break;
        case REVERS_L:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL;
            piece->components[0].x = 0;
            piece->components[0].y = 0;
            //second component
            piece->components[1].row = START_ROW + 1;
            piece->components[1].col = START_COL;
            piece->components[1].x = 0;
            piece->components[1].y = -1;
            //third component rotate around this one
            piece->components[2].row = START_ROW + 2;
            piece->components[2].col = START_COL;
            piece->components[2].x = 0;
            piece->components[2].y = -2;
            //fourth component
            piece->components[3].row = START_ROW + 2;
            piece->components[3].col = START_COL - 1;
            piece->components[3].x = -1;
            piece->components[3].y = -2;
            break;
        case Z:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL - 1;
            piece->components[0].x = -1;
            piece->components[0].y = 0;
            //second component
            piece->components[1].row = START_ROW;
            piece->components[2].col = START_COL;
            piece->components[1].x = 0;
            piece->components[1].y = 0;
            //third component rotate around this one
            piece->components[2].row = START_ROW + 1;
            piece->components[2].col = START_COL;
            piece->components[2].x = 0;
            piece->components[2].y = -1;
            //fourth component
            piece->components[3].row = START_ROW + 1;
            piece->components[3].col = START_COL + 1;
            piece->components[3].x = 1;
            piece->components[3].y = -1;
            break;
        case REVERS_Z:
            //first component
            piece->components[0].row = START_ROW + 1;
            piece->components[0].col = START_COL;
            piece->components[0].x = 0;
            piece->components[0].y = -1;
            //second component rotate around this one
            piece->components[1].row = START_ROW + 1;
            piece->components[1].col = START_COL + 1;
            piece->components[1].x = 1;
            piece->components[1].y = -1;
            //third component
            piece->components[2].row = START_ROW;
            piece->components[2].col = START_COL + 1;
            piece->components[2].x = 1;
            piece->components[2].y = 0;
            //fourth component
            piece->components[3].row = START_ROW;
            piece->components[3].col = START_COL + 2;
            piece->components[3].x = 2;
            piece->components[3].y = 0;
            break;
        case T:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL - 1;
            piece->components[0].x = -1;
            piece->components[0].y = 0;
            //second component rotate around this one
            piece->components[1].row = START_ROW;
            piece->components[1].col = START_COL;
            piece->components[1].x = 0;
            piece->components[1].y = 0;
            //third component
            piece->components[2].row = START_ROW + 1;
            piece->components[2].col = START_COL;
            piece->components[2].x = 0;
            piece->components[2].y = -1;
            //fourth component
            piece->components[3].row = START_ROW;
            piece->components[3].col = START_COL + 1;
            piece->components[3].x = 1;
            piece->components[3].y = 0;
            break;
        default:
            fprintf(stderr, "Invalid piece type generated\n");
            exit(1);
            break;
    }
}

/**
 * Copies the components of a given piece from a source piece to a destination piece.
 * 
 * @param source The piece to copy from.
 * @param destination The piece to copy to.
 */
void copy_piece(Piece* source, Piece* destination) {
    for (int i = 0; i < 4; i++) {
        destination->components[i].row = source->components[i].row;
        destination->components[i].col = source->components[i].col;
        destination->components[i].x = source->components[i].x;
        destination->components[i].y = source->components[i].y;
    }
}

/**
 * Rotate a given piece by a given direction.
 *
 *
 * @param piece The piece to be rotated.
 * @param direction The direction to rotate the piece, either 'a' or 'd'.
 */
void rotate_piece(Piece* piece, char direction) {
    //we multiply by the left rotation matrix
    //RotMat 2X2 times 2X1 = 2X1
    if (direction == LEFT) {
        for (int i = 0; i < 4; i++) {
            int old_x = piece->components[i].x;
            int old_y = piece->components[i].y;

            piece->components[i].x = old_x * left_rotation[0] + old_y * left_rotation[1];
            piece->components[i].y = old_x * left_rotation[2] + old_y * left_rotation[3];

            //apply the rotation to the board coordinates
            piece->components[i].row += piece->components[i].y;
            piece->components[i].col += piece->components[i].x;
        }
    } else if (direction == RIGHT) {
        for (int i = 0; i < 4; i++) {
            int old_x = piece->components[i].x;
            int old_y = piece->components[i].y;

            piece->components[i].x = old_x * right_rotation[0] + old_y * right_rotation[1];
            piece->components[i].y = old_x * right_rotation[2] + old_y * right_rotation[3];

            //apply the rotation to the board coordinates
            piece->components[i].row += piece->components[i].y;
            piece->components[i].col += piece->components[i].x;
        }
    }
}

/**
 * Move a given piece down by one row.
 *
 * This function moves a given piece down by one row by incrementing the
 * row of each component in the piece.
 *
 * @param piece The piece to be moved down.
 */
void move_down(Piece* piece) {
    for (int i = 0; i < 4; i++) {
        piece->components[i].row++;
    }
}

/**
 * Move a given piece to the left by one column.
 *
 * This function moves a given piece to the left by one column by decrementing the
 * column of each component in the piece.
 *
 * @param piece The piece to be moved to the left.
 */
void move_left(Piece* piece) {
    for (int i = 0; i < 4; i++) {
        piece->components[i].col--;
    }
}

/**
 * Move a given piece to the right by one column.
 *
 * This function moves a given piece to the right by one column by incrementing the
 * column of each component in the piece.
 *
 * @param piece The piece to be moved to the right.
 */
void move_right(Piece* piece) {
    for (int i = 0; i < 4; i++) {
        piece->components[i].col++;
    }
}