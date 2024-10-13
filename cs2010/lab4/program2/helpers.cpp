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
void main_loop();
void display_items();
void display_grid(vector<vector<int>> grid);
void add_alive(vector<vector<int>>& grid, int y, int x);
void manual_mode(vector<vector<int>>& grid);
void manual_instructions();
void display_generation(int count);
void print_man_items(int count);
void next_generation(vector<vector<int>>& grid);
int count_neighbors_bfs(vector<vector<int>> grid, int i, int j);
void animation_mode(vector<vector<int>>& grid);
void print_ani_items(int count, int speed);
void animation_instructions();
void display_speed(int speed);

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

    main_loop();
    
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

void main_loop() {
    while(true) {
        
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
            animation_mode(GRID);
            break;                // note: these two break out
        } else if((ch-'0')==2) { //        after modes since 
            manual_mode(GRID);      //         program ends.
            break;
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

void manual_mode(vector<vector<int>>& grid) {

    int count=1;
    print_man_items(0);

    while(true) {
    
        int ch=getch();

        if(ch=='q') 
            break;

        next_generation(GRID);
        print_man_items(count);

        ++count; 
        refresh();
    }
}

void manual_instructions() {
    mvprintw(4, 20, "Press any key to move to the next generation.");
}

void display_generation(int count) {
    mvprintw(8, 16, "Generation : %d", count);
}

void print_man_items(int count) {
        clear(); 
        display_title();
        display_border();
        display_grid(GRID);
        manual_instructions();
        mvprintw(5, 26, "Press 'q' to quit the program.");
        display_generation(count);
}

void next_generation(vector<vector<int>>& grid) {
    int n=grid.size();
    int m=grid[0].size();
    vector<vector<int>> new_grid=grid;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            int neighbors=count_neighbors_bfs(GRID, i, j);
            if(grid[i][j]==1) {
                if(neighbors<2||neighbors>3)
                    new_grid[i][j]=0;
            } else {
                if(neighbors==3)
                    new_grid[i][j]=1;
            }
        }
    }
    grid=new_grid;
}

int count_neighbors_bfs(vector<vector<int>> grid, int i, int j) {

   int count=0;                      // note: this is just a bfs 
   int rows=grid.size();            //        to a depth of 1. 
   int cols=grid[0].size();

   vector<pair<int, int>> directions={
       {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, /*curr*/  {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

   // bfs to depth of 1
   for(const auto& dir : directions) {
       int ni=i+dir.first;                // neighbor indexs initialized
       int nj=j+dir.second;

   if(ni>=0&&ni<rows&&nj>=0&&nj<cols)    // in bounds check
       count+=grid[ni][nj];
    }
   return count;
}

void animation_mode(vector<vector<int>>& grid) {
    int count=1;    
    int delay_speed=100;
    nodelay(stdscr, TRUE); // turn off waiting for getch
    print_ani_items(0, delay_speed);

    while(true) {

        int ch=getch();

        if(ch=='q')
            break;
        else if((ch-'0')==1) {
            if(delay_speed<200)
                delay_speed+=25;
        } else if((ch-'0')==2) {
            if(delay_speed>25) 
                delay_speed-=25;
        }

        napms(delay_speed);
        next_generation(GRID);
        print_ani_items(count, delay_speed);
        ++count;
        refresh();
    }
}

void print_ani_items(int count, int speed) { 
        clear(); 
        display_title();
        display_border();
        display_grid(GRID);
        animation_instructions();
        mvprintw(5, 26, "Press 'q' to quit the program.");
        display_generation(count);
        display_speed(speed);
}

void animation_instructions() {
    mvprintw(4, 20, "Press keys to change Animation Mode options. ");
    mvprintw(7, 45, "1. Increase delay");
    mvprintw(8, 45, "2. Decrease delay");
}

void display_speed(int speed) {
    mvprintw(7, 16, "Delay : %d", speed);
}

















