#include <iostream>
#include "MatrixGraph.h"
#include <vector>

const int infinity=99999; 

// sparse graph 
std::vector<std::vector<int>> test1 = {
    {infinity, 1, infinity, 3, infinity},  
    {infinity, infinity, 5, infinity, infinity}, 
    {infinity, infinity, infinity, infinity, 1},  
    {infinity, infinity, 2, infinity, infinity},  
    {infinity, infinity, infinity, infinity, 6} 
};

// not sparse or dense, in between graph
std::vector<std::vector<int>> test2 = {
    {infinity, 1, infinity, 3, infinity},  
    {infinity, infinity, 5, infinity, 8}, 
    {infinity, infinity, infinity, infinity, 7},  
    {4, infinity, 2, infinity, 9},  
    {infinity, 6, infinity, infinity, 10} 
};

// dense graph
std::vector<std::vector<int>> test3 = {
    {infinity, 1, 5, 3, infinity},  
    {4, 7, 5, infinity, 8}, 
    {6, 2, 9, 3, 7},  
    {4, 8, 2, infinity, 9},  
    {4, 6, infinity, 1, 4} 
};

int main() {


    MatrixGraph m(test3);
    m.print(); 



    return 0; 
}