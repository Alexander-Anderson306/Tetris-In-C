#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include <unistd.h>
//TODO add function to set font size based on terminal size
void set_raw_mode(void);
void reset_terminal(void);

#endif