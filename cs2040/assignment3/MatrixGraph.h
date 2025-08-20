#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include <vector> 

class MatrixGraph {
private: 
    std::vector<std::vector<int> > adjacencyMatrix;

public: 
    MatrixGraph(const std::vector<std::vector<int> >& matrix)
    : adjacencyMatrix(matrix){}; 

    void print(); 
    void dijkstraNoHeap(int start, std::vector<int>& dist, std::vector<int>& pred);
};





#endif // MATRIXGRAPH_H