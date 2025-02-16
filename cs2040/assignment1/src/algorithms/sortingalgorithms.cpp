#include "sortingalgorithms.h"

// sortingalgoirhtms.cpp
// reece hutchison
// sunday feb 16
// sorts a given vector by buuble sort
// input: a vector V[0...n-1] of orderable elements
// output: a vector V[0...n-1] sorted in nondecreasing order
// order of growth: O(n^2)
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
