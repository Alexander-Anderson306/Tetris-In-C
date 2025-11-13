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
            piece->components[0].is_rotation_piece = 0;
            //second component rotate around this one
            piece->components[1].row = START_ROW;
            piece->components[1].col = START_COL;
            piece->components[1].is_rotation_piece = 1;
            //third component
            piece->components[2].row = START_ROW;
            piece->components[2].col = START_COL + 1;
            piece->components[2].is_rotation_piece = 0;
            //fourth component
            piece->components[3].row = START_ROW;
            piece->components[3].col = START_COL + 2;
            piece->components[3].is_rotation_piece = 0;
            break;
        case SQUARE:
            //first component rotate around this one
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL;
            piece->components[0].is_rotation_piece = 1;
            //second component
            piece->components[1].row = START_ROW;
            piece->components[1].col = START_COL + 1;
            piece->components[1].is_rotation_piece = 0;
            //third component
            piece->components[2].row = START_ROW + 1;
            piece->components[2].col = START_COL;
            piece->components[2].is_rotation_piece = 0;
            //fourth component
            piece->components[3].row = START_ROW + 1;
            piece->components[3].col = START_COL + 1;
            piece->components[3].is_rotation_piece = 0;
            break;
        case L:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL;
            piece->components[0].is_rotation_piece = 0;
            //second component
            piece->components[1].row = START_ROW + 1;
            piece->components[1].col = START_COL;
            piece->components[1].is_rotation_piece = 0;
            //third component rotate around this one
            piece->components[2].row = START_ROW + 2;
            piece->components[2].col = START_COL;
            piece->components[2].is_rotation_piece = 1;
            //fourth component
            piece->components[3].row = START_ROW + 2;
            piece->components[3].col = START_COL + 1;
            piece->components[3].is_rotation_piece = 0;
            break;
        case REVERS_L:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL;
            piece->components[0].is_rotation_piece = 0;
            //second component
            piece->components[1].row = START_ROW + 1;
            piece->components[1].col = START_COL;
            piece->components[1].is_rotation_piece = 0;
            //third component rotate around this one
            piece->components[2].row = START_ROW + 2;
            piece->components[2].col = START_COL;
            piece->components[2].is_rotation_piece = 1;
            //fourth component
            piece->components[3].row = START_ROW + 2;
            piece->components[3].col = START_COL - 1;
            piece->components[3].is_rotation_piece = 0;
            break;
        case Z:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL-1;
            piece->components[0].is_rotation_piece = 0;
            //second component
            piece->components[1].row = START_ROW;
            piece->components[2].col = START_COL;
            piece->components[1].is_rotation_piece = 0;
            //third component rotate around this one
            piece->components[2].row = START_ROW + 1;
            piece->components[2].col = START_COL;
            piece->components[2].is_rotation_piece = 1;
            //fourth component
            piece->components[3].row = START_ROW + 1;
            piece->components[3].col = START_COL + 1;
            piece->components[3].is_rotation_piece = 0;
            break;
        case REVERS_Z:
            //first component
            piece->components[0].row = START_ROW + 1;
            piece->components[0].col = START_COL;
            piece->components[0].is_rotation_piece = 0;
            //second component rotate around this one
            piece->components[1].row = START_ROW + 1;
            piece->components[1].col = START_COL + 1;
            piece->components[1].is_rotation_piece = 1;
            //third component
            piece->components[2].row = START_ROW;
            piece->components[2].col = START_COL + 1;
            piece->components[2].is_rotation_piece = 0;
            //fourth component
            piece->components[3].row = START_ROW;
            piece->components[3].col = START_COL + 2;
            piece->components[3].is_rotation_piece = 0;
            break;
        case T:
            //first component
            piece->components[0].row = START_ROW;
            piece->components[0].col = START_COL - 1;
            piece->components[0].is_rotation_piece = 0;
            //second component rotate around this one
            piece->components[1].row = START_ROW;
            piece->components[1].col = START_COL;
            piece->components[1].is_rotation_piece = 1;
            //third component
            piece->components[2].row = START_ROW + 1;
            piece->components[2].col = START_COL;
            piece->components[2].is_rotation_piece = 0;
            //fourth component
            piece->components[3].row = START_ROW;
            piece->components[3].col = START_COL + 1;
            piece->components[3].is_rotation_piece = 0;
            break;
        default:
            fprintf(stderr, "Invalid piece type generated\n");
            exit(1);
            break;
    }
}