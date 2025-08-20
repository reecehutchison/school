#include "MatrixGraph.h"

#include <iostream>
#include <vector>

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

void MatrixGraph::dijkstraNoHeap(int start, std::vector<int>& dist, std::vector<int>& pred) {
    int n = adjacencyMatrix.size();
    std::vector<bool> visited(n, false);
    dist.resize(n, infinity);
    pred.resize(n, -1);
    dist[start]=0;
    for (int count=0; count<n-1; ++count) {
        int u = -1;
        int min_dist = infinity;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }
        if (u == -1) break; 
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && adjacencyMatrix[u][v] != infinity) {
                int new_dist = dist[u] + adjacencyMatrix[u][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pred[v] = u; 
                }
            }
        }
    }
}