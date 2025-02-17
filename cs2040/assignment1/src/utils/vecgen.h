#ifndef VECGEN_H
#define VECGEN_H

#include <vector>
#include <random>
#include <algorithm>

// this header file includes the test array creation function for the tests

class VecGen {
public:
    
    // note: sorted is low to high, reverse sorted is high to low...

    // generates a random array based off given size
    std::vector<int> generateRandomVector(int size);

    // generates a sorted array based of given size
    std::vector<int> generateSortedVector(std::vector<int> vec);

    // generates a reverse-sorted array based of size given
    std::vector<int> generateReverseVector(std::vector<int> vec);
};

#endif
