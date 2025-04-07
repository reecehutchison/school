#include "MatrixGraph.h"

#include <iostream>

const int infinity=99999; 

void MatrixGraph::print() {
    int n=this->adjacencyMatrix.size(); 
    std::cout << "Vertices | Edge Weight\n"; 
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(this->adjacencyMatrix[i][j]!=infinity) {
                std::cout << i << " --> " << j << "        " 
                << this->adjacencyMatrix[i][j] << "\n";
            }
        }
    }
}