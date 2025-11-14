#ifndef GAME_H
#define GAME_H

#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "board.h"
#include "piece.h"
#include "terminal.h"

#define USER_TICK_RATE 166667

//its looking like we will need three threads
//one for gravity
//one for user input
//one for checking for clears and scoreing

//for my tetris one line clear is 100 points
//two line clear is 250 points
//three line clear is 500 points
//four line clear is 1000 points
void game_loop(Board* board);
int check_for_clears(Board* board);
int update_fall_tick_rate(int score);

#endif