#include "sortingalgorithms.h"

// sortingalgoirhtms.cpp
// reece hutchison
// sunday feb 16
// sorts a given vector by buuble sort
// input: a vector V[0...n-1] of orderable elements
// output: a vector V[0...n-1] sorted in nondecreasing order
// time complexity: O(n^2)
// space complexity: O(1)
// stability: bubble sort is stable
void SortingAlgorithms::bubbleSort(std::vector<int>& vec) {
    int n=vec.size(); 
    for(int i=0; i<n-1; ++i) {
        for(int j=0; j<n-1-i; ++j) {
            if(vec[j+1]<vec[j]) { // basic opperation in this function is 
                int tmp=vec[j];   // the comparison
                vec[j]=vec[j+1];
                vec[j+1]=tmp;
            }
        }
    }
}

// sortingalgorithms.cpp
// reece hutchision
// sunday feb 16
// sorts a given array by selection sort
// input: a vector V[0...n-1] of orderable eleemnts
// output: a vector V[0...n-1] sorted in nondecreasing order
// time complexity: O(n^2)
// space complexity: O(1)
// stability: selection sort is not stable
void SortingAlgorithms::selectionSort(std::vector<int>& vec) {
    int n=vec.size();
    for(int i=0; i<n-1; ++i) {
        int min=i;
        for(int j=i+1; j<n; ++j) {
            if(vec[j]<vec[min])
                min=j;
        }
        int tmp=vec[i];
        vec[i]=vec[min];
        vec[min]=tmp;
    }
}

// sortingalgorithms.cpp
// reece hutchison
// sunday feb 16
// sorts given vector by insertion sort
// input: a vector V[0...n-1] of n orderable elements
// output: a vector V[0...n-1] sorted in nondecreasing order
// time complexity: O(n^2)
// space complexity: O(1)
// staboloty: insertion sort is stable
void SortingAlgorithms::insertionSort(std::vector<int>& vec) {
    int n=vec.size();
    for(int i=1; i<n; ++i) {
        int v=vec[i];
        int j=i-1;
        while(j>=0 && vec[j]>v) {
            vec[j+1]=vec[j];
            j=j-1;
        }
        vec[j+1]=v;
    }
}



