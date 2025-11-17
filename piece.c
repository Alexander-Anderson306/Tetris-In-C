#include "piece.h"
#include "board.h"

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
    enum Piece_Type type = (enum Piece_Type) rand() % 7;
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
            piece->components[0].col = START_COL-1;
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
    destination->type = source->type;
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
    if (direction == ROTATE_LEFT) {
        for (int i = 0; i < 4; i++) {
            int old_x = piece->components[i].x;
            int old_y = piece->components[i].y;

            piece->components[i].x = old_x * left_rotation[0] + old_y * left_rotation[1];
            piece->components[i].y = old_x * left_rotation[2] + old_y * left_rotation[3];

            //apply the rotation to the board coordinates
            piece->components[i].row += piece->components[i].y;
            piece->components[i].col += piece->components[i].x;
        }
    } else if (direction == ROTATE_RIGHT) {
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
 * Move a given piece in a given direction.
 *
 * @param piece The piece to be moved.
 * @param direction The direction to move the piece, either 'a' for left or 'd' for right.
 */
void move_piece(Piece* piece, Board* board, char direction) {
    char stop_flag = 0;
    switch(direction) {
        case LEFT:
            piece->components[0].col--;
            piece->components[1].col--;
            piece->components[2].col--;
            piece->components[3].col--;
            break;
        case RIGHT:
            piece->components[0].col++;
            piece->components[1].col++;
            piece->components[2].col++;
            piece->components[3].col++;
            break;
        case DROP:
            while(!stop_flag) {
                //check if the piece can move down again
                for (int i = 0; i < 4; i++) {

                    int row = piece->components[i].row;
                    int col = piece->components[i].col;

                    //look at the cell below
                    int below_row = row + 1;
                    int below_col = col;

                    char below = board->character_board[below_row][below_col];

                    //if the cell below is not empty make sure its not part of the same piece
                    if (below != EMPTY_SPACE) {
                        char same_piece = 0;

                        for (int j = 0; j < 4; j++) {
                            if (piece->components[j].row == below_row &&
                                piece->components[j].col == below_col) {
                                same_piece = 1;
                                break;
                            }
                        }

                        if (!same_piece) {
                            stop_flag = 1;
                        }
                    }
                }

                //move the piece down
                if(!stop_flag) {
                    piece->components[0].row++;
                    piece->components[1].row++;
                    piece->components[2].row++;
                    piece->components[3].row++;
                }
            }

            //push the piece back up one sloppy fix for bug
            piece->components[0].row--;
            piece->components[1].row--;
            piece->components[2].row--;
            piece->components[3].row--;
            break;
        default:
            fprintf(stderr, "Invalid direction generated\nDirection: %c\n", direction);
            exit(1);
            break;
    }
}



/**
 * Move a given piece down one row.
 * This is used to simulate gravity in the game.
 *
 * @param piece The piece to be moved down.
 */
void gravity_tick(Piece* piece) {
    //move the piece down
    piece->components[0].row++;
    piece->components[1].row++;
    piece->components[2].row++;
    piece->components[3].row++;
}