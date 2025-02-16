#include "prgdisplay.h"


// starts ncurses with desired setup to display resulting data
void PrgDisplay::initializeNcurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

// destorys the ncurses window and returns to normal terminal behaviour
void PrgDisplay::cleanupNcurses() {
    endwin();
}
