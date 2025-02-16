#include "prgdisplay.h"

// prgdisplay.cpp
// reece hutchsion
// sunday feb 16
// starts ncurses window with desired behaviour
// input: nothing
// output: nothing
void PrgDisplay::initializeNcurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

// progdisplay.cpp
// reece hutchison
// sunday feb 16
// destorys the ncurses window and returns to normal terminal behaviour
// input: nothing
// output: nothing
void PrgDisplay::cleanupNcurses() {
    endwin();
}
