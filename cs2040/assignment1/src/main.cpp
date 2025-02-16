#include "display/prgdisplay.h"
#include "utils/stopwatch.h"
#include "utils/vecgen.h"
#include "algorithms/sortingalgorithms.h"
#include <vector>
#include <iostream>

// main.cpp
// reece hutchison
// sunday feb 16
// evaluates the different runtime of quicksort, mergesort, insertion sort, 
// selection sort, and bubble sort, and displays the results
// input: no flags are required (no input)
// output: a table with the resulting information about the runtimes of 
// the sorting algorithms
int main() {
   
    // initialize objects
    PrgDisplay display;
    Stopwatch timer;
    VecGen gen; 
    SortingAlgorithms sorter;

    
    // being to call sorting functions and record their data here

    std::vector<int> vec=gen.generateRandomVector(10);
    for(auto e : vec)
        std::cout << e << " ";
    std::cout << "\n";
    
    sorter.insertionSort(vec);

    for(auto e : vec)
        std::cout << e << " ";
    std::cout << "\n";




/* ncurses stuff when readdyy !!!!!!!!!!!!!!!!!!!!11

    // begin calling display functions here
    display.initializeNcurses(); 
    


    // program ends here, and waits for user input to exit
    refresh();
    getch();
    display.cleanupNcurses(); 
*/

    return 0;
}
