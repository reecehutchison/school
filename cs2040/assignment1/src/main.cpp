#include "utils/stopwatch.h"
#include "utils/vecgen.h"
#include "algorithms/sortingalgorithms.h"
#include <vector>
#include <iostream>
#include <iomanip>

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
    Stopwatch timer;
    VecGen gen; 
    SortingAlgorithms sorter;


    // lists of initial small vectors
    std::vector<std::vector<int>> randomListSmall; 
    int n1=100000; // size of vectors
    for(int i=0; i<10; ++i) 
        randomListSmall.push_back(gen.generateRandomVector(n1));

    std::vector<std::vector<int>> sortedListSmall; 
    for(int i=0; i<10; ++i)
        sortedListSmall.push_back(gen.generateSortedVector(randomListSmall[i]));

    std::vector<std::vector<int>> reverseListSmall; 
    for(int i=0; i<10; ++i) 
        reverseListSmall.push_back(gen.generateReverseVector(randomListSmall[i]));


    // lists of initial medium vectors
    std::vector<std::vector<int>> randomListMed; 
    int n2=1000000; // size of vectors
    for(int i=0; i<10; ++i) 
        randomListMed.push_back(gen.generateRandomVector(n2));

    std::vector<std::vector<int>> sortedListMed; 
    for(int i=0; i<10; ++i)
        sortedListMed.push_back(gen.generateSortedVector(randomListMed[i]));

    std::vector<std::vector<int>> reverseListMed; 
    for(int i=0; i<10; ++i) 
        reverseListMed.push_back(gen.generateReverseVector(randomListMed[i]));


    // lists of initial large vectors
    std::vector<std::vector<int>> randomListLarge; 
    int n3=10000000; // size of vectors
    for(int i=0; i<10; ++i) 
        randomListLarge.push_back(gen.generateRandomVector(n3));

    std::vector<std::vector<int>> sortedListLarge; 
    for(int i=0; i<10; ++i)
        sortedListLarge.push_back(gen.generateSortedVector(randomListLarge[i]));

    std::vector<std::vector<int>> reverseListLarge; 
    for(int i=0; i<10; ++i) 
        reverseListLarge.push_back(gen.generateReverseVector(randomListLarge[i]));


    // ------------------------------------------------------
    // 1. quick sort
    std::vector<std::vector<int>> qsRandomListSmall=randomListSmall;
    std::vector<std::vector<int>> qsSortedListSmall=sortedListSmall;
    std::vector<std::vector<int>> qsReverseListSmall=reverseListSmall;

    std::vector<std::vector<int>> qsRandomListMed=reverseListMed;
    std::vector<std::vector<int>> qsSortedListMed=reverseListMed;
    std::vector<std::vector<int>> qsReverseListMed=reverseListMed;

    std::vector<std::vector<int>> qsRandomListLarge=reverseListLarge;
    std::vector<std::vector<int>> qsSortedListLarge=reverseListLarge;
    std::vector<std::vector<int>> qsReverseListLarge=reverseListLarge;
    
    std::cout << "\n\n";
    std::cout << "----------------------------------------------------\n";
    std::cout << "Quick Sort Runtime in Miliseconds\n";
    std::cout << "n = 100,000\n";
    // random list small
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsRandomListSmall[i], 0, qsRandomListSmall.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list small
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsSortedListSmall[i], 0, qsSortedListSmall.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list small
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsReverseListSmall[i], 0, qsReverseListSmall.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    std::cout << "n = 1,000,000\n";

    // random list medium
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsRandomListMed[i], 0, qsRandomListMed.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list medium
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsSortedListMed[i], 0, qsSortedListMed.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list med
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsReverseListMed[i], 0, qsReverseListMed.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    std::cout << "n = 10,000,000\n";

    // random list large
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsRandomListLarge[i], 0, qsRandomListLarge.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list large
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsSortedListLarge[i], 0, qsSortedListLarge.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list large
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.quickSort(qsReverseListLarge[i], 0, qsReverseListLarge.size()-1);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";




    // ------------------------------------------------------
    // 2. merge sort
    std::vector<std::vector<int>> msRandomListSmall=randomListSmall;
    std::vector<std::vector<int>> msSortedListSmall=sortedListSmall;
    std::vector<std::vector<int>> msReverseListSmall=reverseListSmall;

    std::vector<std::vector<int>> msRandomListMed=reverseListMed;
    std::vector<std::vector<int>> msSortedListMed=reverseListMed;
    std::vector<std::vector<int>> msReverseListMed=reverseListMed;

    std::vector<std::vector<int>> msRandomListLarge=reverseListLarge;
    std::vector<std::vector<int>> msSortedListLarge=reverseListLarge;
    std::vector<std::vector<int>> msReverseListLarge=reverseListLarge;

    std::cout << "\n";
    std::cout << "----------------------------------------------------\n";
    std::cout << "Merge Sort Runtime in Miliseconds\n";
    std::cout << "n = 100,000\n";
    // random list small
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msRandomListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list small
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msSortedListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list small
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msReverseListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";

    std::cout << "n = 1,000,000\n";

    // random list medium
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msRandomListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list medium
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msSortedListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list med
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msReverseListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    std::cout << "n = 10,000,000\n";

    // random list large
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msRandomListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list large
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msSortedListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list large
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.mergeSort(msReverseListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";

    // ------------------------------------------------------
    // 2. insertion sort
    std::vector<std::vector<int>> isRandomListSmall=randomListSmall;
    std::vector<std::vector<int>> isSortedListSmall=sortedListSmall;
    std::vector<std::vector<int>> isReverseListSmall=reverseListSmall;

    std::vector<std::vector<int>> isRandomListMed=reverseListMed;
    std::vector<std::vector<int>> isSortedListMed=reverseListMed;
    std::vector<std::vector<int>> isReverseListMed=reverseListMed;

    std::vector<std::vector<int>> isRandomListLarge=reverseListLarge;
    std::vector<std::vector<int>> isSortedListLarge=reverseListLarge;
    std::vector<std::vector<int>> isReverseListLarge=reverseListLarge;

    std::cout << "\n";
    std::cout << "----------------------------------------------------\n";
    std::cout << "Insertion Sort Runtime in Miliseconds\n";
    std::cout << "n = 100,000\n";
    // random list small
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isRandomListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list small
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isSortedListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list small
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isReverseListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";

    std::cout << "n = 1,000,000\n";

    // random list medium
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isRandomListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list medium
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isSortedListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list med
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isReverseListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    std::cout << "n = 10,000,000\n";

    // random list large
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isRandomListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list large
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isSortedListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list large
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.insertionSort(isReverseListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    // ------------------------------------------------------
    // 4. insertion sort
    std::vector<std::vector<int>> ssRandomListSmall=randomListSmall;
    std::vector<std::vector<int>> ssSortedListSmall=sortedListSmall;
    std::vector<std::vector<int>> ssReverseListSmall=reverseListSmall;

    std::vector<std::vector<int>> ssRandomListMed=reverseListMed;
    std::vector<std::vector<int>> ssSortedListMed=reverseListMed;
    std::vector<std::vector<int>> ssReverseListMed=reverseListMed;

    std::vector<std::vector<int>> ssRandomListLarge=reverseListLarge;
    std::vector<std::vector<int>> ssSortedListLarge=reverseListLarge;
    std::vector<std::vector<int>> ssReverseListLarge=reverseListLarge;

    std::cout << "\n";
    std::cout << "----------------------------------------------------\n";
    std::cout << "Selection Sort Runtime in Miliseconds\n";
    std::cout << "n = 100,000\n";
    // random list small
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssRandomListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list small
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssSortedListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list small
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssReverseListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";

    std::cout << "n = 1,000,000\n";

    // random list medium
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssRandomListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list medium
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssSortedListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list med
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssReverseListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    std::cout << "n = 10,000,000\n";

    // random list large
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssRandomListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list large
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssSortedListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list large
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.selectionSort(ssReverseListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    // ------------------------------------------------------
    // 5. insertion sort
    std::vector<std::vector<int>> bsRandomListSmall=randomListSmall;
    std::vector<std::vector<int>> bsSortedListSmall=sortedListSmall;
    std::vector<std::vector<int>> bsReverseListSmall=reverseListSmall;

    std::vector<std::vector<int>> bsRandomListMed=reverseListMed;
    std::vector<std::vector<int>> bsSortedListMed=reverseListMed;
    std::vector<std::vector<int>> bsReverseListMed=reverseListMed;

    std::vector<std::vector<int>> bsRandomListLarge=reverseListLarge;
    std::vector<std::vector<int>> bsSortedListLarge=reverseListLarge;
    std::vector<std::vector<int>> bsReverseListLarge=reverseListLarge;

    std::cout << "\n";
    std::cout << "----------------------------------------------------\n";
    std::cout << "Bubble Sort Runtime in Miliseconds\n";
    std::cout << "n = 100,000\n";
    // random list small
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsRandomListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list small
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsSortedListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list small
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsReverseListSmall[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";

    std::cout << "n = 1,000,000\n";

    // random list medium
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsRandomListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list medium
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsSortedListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list med
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsReverseListMed[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";


    std::cout << "n = 10,000,000\n";

    // random list large
    std:: cout << "Random Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsRandomListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // sorted list large
    std:: cout << "Sorted Arrays:  "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsSortedListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";
    
    // reverse list large
    std:: cout << "Reverse Arrays: "; 
    for(int i=0; i<10; ++i) {
        timer.start(); 
        sorter.bubbleSort(bsReverseListLarge[i]);
        timer.stop();
        std::cout << std::fixed << std::setprecision(6) << timer.getElapsedMilliseconds();
        if(i!=9)
            std::cout << " | ";
    }
    std::cout << "\n";




    std::cout << "\n\n\n";
    return 0;
}
