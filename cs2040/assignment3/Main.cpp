#include <iostream>
#include "MatrixGraph.h"
#include <vector>

const int infinity=99999; 

// sparse graph 
std::vector<std::vector<int>> test1 = {
    {infinity, 1, infinity, infinity, infinity},  
    {infinity, infinity, 5, 3, infinity}, 
    {infinity, infinity, infinity, infinity, 1},  
    {infinity, infinity, 2, infinity, infinity},  
    {infinity, 9, infinity, infinity, infinity} 
};

// not sparse or dense, in between graph (make still)
std::vector<std::vector<int>> test2 = {
    {infinity, infinity, infinity, infinity, infinity},  
    {infinity, infinity, infinity, infinity, infinity}, 
    {infinity, infinity, infinity, infinity, infinity},  
    {infinity, infinity, infinity, infinity, infinity},  
    {infinity, infinity, infinity, infinity, infinity} 
};

// dense graph (make still)
std::vector<std::vector<int>> test3 = {
    {infinity, infinity, infinity, infinity, infinity},  
    {infinity, infinity, infinity, infinity, infinity}, 
    {infinity, infinity, infinity, infinity, infinity},  
    {infinity, infinity, infinity, infinity, infinity},  
    {infinity, infinity, infinity, infinity, infinity} 
};

int main() {


    MatrixGraph m(test1);
    m.print(); 
    std::vector<int> dist;
    std::vector<int> pred; 
    m.dijkstraNoHeap(0, dist, pred); 

    for(int i=0; i<dist.size(); ++i) {
        std::cout << i << ") pred: " << pred[i] 
        << " | dist: " << dist[i] << std::endl; 
    }



    return 0; 
}