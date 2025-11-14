#include "terminal.h"
static struct termios old_settings;

void set_raw_mode(void) {
    struct termios new_settings;
    //backup current terminal settings
    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;

    //disable ICANON (process by character not by line)
    //disable ECHO (no repeating echo to terminal)
    new_settings.c_lflag &= ~(ICANON | ECHO);
    //read now returns even if 0 characters are read
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void reset_terminal(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}