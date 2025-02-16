#include "display/prgdisplay.h"
#include "utils/stopwatch.h"
#include "utils/vecgen.h"
#include <vector>
#include <iostream>

int main() {
   
    // initialize objects
    PrgDisplay display;
    Stopwatch timer;
    VecGen gen; 

    
    // being to call sorting functions and record their data here




    // begin calling display functions here
    display.initializeNcurses(); 
    


    // program ends here, and waits for user input to exit
    refresh();
    getch();
    display.cleanupNcurses(); 

    return 0;
}
