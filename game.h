#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include <string.h>
#include "board.h"
#include "piece.h"
#include "terminal.h"

#define USER_TICK_RATE 166667

//its looking like we will need two threads
//one for gravity
//one for user input

typedef struct Thread_Args {
    Board* board;
    Piece* piece;
} Thread_Args;

//for my tetris one line clear is 100 points
//two line clear is 250 points
//three line clear is 500 points
//four line clear is 1000 points
void game_loop(Board* board);
int check_for_clears_and_score(Board* board, int tick_rate);
int update_fall_tick_rate(int score);

#endif