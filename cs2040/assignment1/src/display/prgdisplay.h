#ifndef PRGDISPLAY_H
#define PRGDISPLAY_H

// this header file includes all of the functions that will 
// display the data results using the ncurses library to 
// help simplify the task. 


#include <ncurses.h>

class PrgDisplay {
public:
    // initializes and sets up ncurses mode
    void initializeNcurses(); 

    // ends ncurses mode
    void cleanupNcurses(); 
};

#endif
