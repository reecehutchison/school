#include "database.h"
#include <stdio.h>
#include <ncurses.h>


#define STUDENT_FILE "student.data"
#define STRING_LENGTH 99




void init_ncurses() {
    initscr();
    cbreak();                // disables line buffering
    noecho();               // turns of echoing of typed charecters
    keypad(stdscr, TRUE);  // enables keypad input 
    curs_set(0);          // disable cursor
    return;
}

void display_debug_info(int ch) {
    mvprintw(27, 3, "key: %c",ch);
    return;
}
