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

// sortingalgorithms.cpp
// reece hutchison
// sunday feb 16
// sorts given vector by recursive merge sort
// input: a vector V[0...n-1] of orderable elements
// output: a vector V[0...n-1] sorted in nondecreasing order
// time complexity: O(nlogn)
// space complexity: O(n)
// stability: merge sort is stable
void SortingAlgorithms::mergeSort(std::vector<int>& vec) {
    int n=vec.size();
    if(n>1) {
        std::vector<int> left;
        std::vector<int> right;
        for(int i=0; i<n; ++i) {
            if(i<(n/2))
                left.push_back(vec[i]);
            else 
                right.push_back(vec[i]);
        }
        mergeSort(left); 
        mergeSort(right);
        merge(vec, left, right);
    }
}

// sortingalgorithms.cpp
// reece hutchison
// sunday feb 16
// merges two sored arrays into one sorted array
// input: vectors left[0...n/2-1] and right[0...n-n/2-1] both sorted
// output: a vector V[0...n-1] of elements left and right
// note: used in merge sort!
void SortingAlgorithms::merge(std::vector<int>& vec, std::vector<int>& left, std::vector<int>& right) {
    int n=vec.size(); 
    int i=0; 
    int j=0;
    int k=0;
    while(i<(n/2) && j<(n-n/2)) {
        if(left[i]<=right[j]) 
            vec[k++]=left[i++];
        else 
            vec[k++]=right[j++]; 
    }
    while(i<(n/2)) 
        vec[k++]=left[i++];
    
    while(j<(n-n/2)) 
        vec[k++]=right[j++]; 
}

// sortingalgorithms.cpp
// reece hutchison
// sunday feb 16
// sorts a subvector by quicksort
// input: a subvector V[0...n-1] defined by left and right indecies
// output: a subvector V[l...r] sorted in nondecreasing order
// time complexty: O(nlogn)
// space complexity: O(logn) --> requres space on call stack
// stability: quick sort is not stable
void SortingAlgorithms::quickSort(std::vector<int>& vec, int left, int right) {
    if(left<right) {
        int s=partition(vec, left, right);
        quickSort(vec, left, s-1);
        quickSort(vec, s+1, right);
    }
}

// sortingalgorithms.cpp
// reece hutchison
// sunday feb 16
// partitions a subarray by hoare's algorithm, using first element as pivot
// input: subvector of vector V[0...n-1], defined by left and right
// output: partition of V[l...r] with split position returned by function
// note: used in quicksort!
int SortingAlgorithms::partition(std::vector<int>& vec, int left, int right) {
    int p=vec[left];  
    int i=left+1;   
    int j=right;      

    while(1) {
        while(i<=right && vec[i]<=p) 
            i++;
        while(vec[j]>p) 
            j--;
        if (i>=j) break; // breaking out early prevents undoing last swap

        int tmp=vec[i];  // swap vec[i] and vec[j]
        vec[i]=vec[j];   
        vec[j]=tmp;
    }

    int tmp=vec[left]; // swap vec[left] and vec[j]
    vec[left]=vec[j];
    vec[j]=tmp;

    return j;
}
