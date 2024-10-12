//
//  helpers.cpp
//  cs2010_lab4
//
//  Created by Reece Hutchison on 2024-10-10.
//

#include <ncurses.h>
#include <vector>

using namespace std;

void game_of_life();
void display_border(); 
void display_title();
void display_instructions();
void debug_on_or_off();
void debugger(int ch, MEVENT event);
void initialize_ncurses();
void starting_loop();
void display_items();
void display_grid(vector<vector<int>> grid);
void add_alive(vector<vector<int>>& grid, int y, int x);

const int HEIGHT=32;
const int WIDTH=64;

vector<vector<int>> GRID(HEIGHT, vector<int>(WIDTH, 0));


// DEBUG MODE
bool DEBUG_MODE=false;

void game_of_life() {


    initialize_ncurses();

    clear();
    display_items(); 
    if(DEBUG_MODE)
        mvprintw(46, 0, "waiting for input...");

    starting_loop();

    
    endwin(); // ends ncurses system
}

void display_border() {

    mvprintw(10, 6, "+");
    mvprintw(10, WIDTH+7, "+");
    for(int i=7; i<WIDTH+7; ++i) 
        mvprintw(10, i, "-");

    for(int i=11; i<HEIGHT+11; ++i) {
        mvprintw(i, 6, "|");
        mvprintw(i, WIDTH+7, "|");
    }

    mvprintw(HEIGHT+11, 6, "+");
    mvprintw(HEIGHT+11, WIDTH+7, "+");
    for(int i=7; i<WIDTH+7; ++i) 
        mvprintw(HEIGHT+11, i, "-");
}

void display_title() {
    mvprintw(2, 20, "~~-~~-~~ Conway's Game of Life ~~-~~-~~");
}

void display_instructions() {
    mvprintw(4, 16, "Click within the border to place alive cells.");
    mvprintw(5, 16, "Press numbers to select options listed below.");
    mvprintw(7, 16, "1. Start in Animated Mode");
    mvprintw(8, 16, "2. Start in Manual Mode");
    mvprintw(7, 45, "3. Debugger Mode");
    mvprintw(8, 45, "4. Quit Program");
}

void debug_on_or_off() {
    if(DEBUG_MODE)
        mvprintw(45, 0, "(debug mode : ON)");
    else
        mvprintw(45, 0, "(debug mode : OFF)");
}

void debugger(int ch, MEVENT event) {
    if (ch==KEY_MOUSE) {
        //if (getmouse(&event)==OK)
            mvprintw(46, 0, "mouse at: y = %d, x = %d", event.y, event.x); 
    } else if(ch==' ')    
        mvprintw(46, 0, "char clicked : space");
    else
        mvprintw(46, 0, "char clicked : %c", ch);
}

void initialize_ncurses() {
    initscr();                // initializes ncurses system
    cbreak();                // disables line buffering
    noecho();               // turns of echoing of typed charecters
    keypad(stdscr, TRUE);  // enables keypad input
    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION, NULL); // enables the mouse
    mouseinterval(0);  // Set mouse click resolution
    curs_set(0); // disable cursor
}

void starting_loop() {
    while (true) {
        
        int ch=getch();
        clear();
        MEVENT event;

        if(ch==KEY_MOUSE) {
            if(getmouse(&event)==OK) {
                int y=event.y;
                int x=event.x;
                add_alive(GRID, y, x);
            }    
        } else if((ch-'0')==1) {
            // animated
        } else if((ch-'0')==2) {
            // manual mode
        } else if((ch-'0')==3) {
            if(DEBUG_MODE==false)
                DEBUG_MODE=true;
            else
                DEBUG_MODE=false;
        } else if((ch-'0')==4)
            break;

        if(DEBUG_MODE) 
            debugger(ch, event);

        display_items();
                        
        refresh();
    }
}

void display_items() {
    display_title();
    display_border();
    display_instructions();
    debug_on_or_off();
    display_grid(GRID);
}

void display_grid(vector<vector<int>> grid) {
    int n=grid.size();
    int m=grid[0].size();

    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(grid[i][j]==1) {
                mvprintw(i+11, j+7, "X");
            }
        }
    }
}

void add_alive(vector<vector<int>>& grid, int y, int x) {
    if(y>=11&&y<=42&&x>=7&&x<=70) { 
        if(grid[y-11][x-7]==0)
            grid[y-11][x-7]=1;
        else
            grid[y-11][x-7]=0;
        if(DEBUG_MODE)
            mvprintw(0, 0, "grid updated");
    } else {
        if(DEBUG_MODE)
            mvprintw(0, 0, "grid NOT updated");
    }
}













