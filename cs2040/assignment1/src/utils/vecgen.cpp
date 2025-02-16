#include "vecgen.h"

// returns a random array of size n, where n is the given size
std::vector<int> VecGen::generateRandomVector(int size) {
    std::vector<int> vec;

    std::random_device rd; // note, this part sets up a random device
    std::mt19937 gen(rd()); // that will get random numbers from 1 to 1000000.
    std::uniform_int_distribution<int> dist(1, 1000000);

    for(int i=0; i<size; ++i) {
        int randomNumber=dist(gen);
        vec.push_back(randomNumber);
    }

    return vec;
}

// returns array in sorted order
std::vector<int> VecGen::generateSortedVector(int size) {
    std::vector<int> vec;

    for(int i=1; i<size+1; ++i) {
        vec.push_back(i);
    }

    return vec;
}

// returns an array in reverse sorted order...
std::vector<int> VecGen::generateReverseVector(int size) {
    std::vector<int> vec;

    for(int i=size; i>0; --i) {
        vec.push_back(i);
    }

    return vec;
}
