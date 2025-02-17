#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

// this header file includes the sorting algorithms 


#include <vector>

class SortingAlgorithms {
public:
    SortingAlgorithms()=default;

    // bubble sort
    void bubbleSort(std::vector<int>& vec);

    // insertion sort
    void insertionSort(std::vector<int>& vec);

    // selection sort
    void selectionSort(std::vector<int>& vec);

    // merge sort
    void mergeSort(std::vector<int>& vec);
    void merge(std::vector<int>& vec, std::vector<int>& left, std::vector<int>& right);

    // quick sort
    void quickSort(std::vector<int>& vec, int left, int right);
    int partition(std::vector<int>& vec, int left, int right);
};

#endif 
