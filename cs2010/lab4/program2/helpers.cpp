//
//  helpers.cpp
//  cs2010_lab4
//
//  Created by Reece Hutchison on 2024-10-10.
//

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstring>

using namespace std;

void game_of_life() {
    
    initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
    
}


