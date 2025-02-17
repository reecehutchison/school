#include "vecgen.h"

// vecgen.cpp
// reece hutchison
// sunday feb 16
// returns a random array of size n, where n is the given size
// input: size of of vector wanted
// output: vector of random elements of size wanted
std::vector<int> VecGen::generateRandomVector(int size) {
    std::vector<int> vec;

    std::random_device rd; // note, this part sets up a random device
    std::mt19937 gen(rd()); // that will get random numbers from 1 to n
    int n=1000000;
    std::uniform_int_distribution<int> dist(1, n);

    for(int i=0; i<size; ++i) {
        int randomNumber=dist(gen);
        vec.push_back(randomNumber);
    }

    return vec;
}

// vecgen.cpp
// reece hutchison
// sunday feb 16 
// sorts the random vector so its in sorted order
// input: size you want the vector to be
// output: a vector of the size you wanted in sorted order
std::vector<int> VecGen::generateSortedVector(std::vector<int> vec) {
    sort(vec.begin(), vec.end());
    return vec;
}

// vecgen.cpp
// reece hutchison
// sunday feb 16
// returns an array in reverse sorted order
// input: the size you want the vector to be
// output: the vector in reverse order of the desired size
std::vector<int> VecGen::generateReverseVector(std::vector<int> vec) {
    sort(vec.rbegin(), vec.rend());
    return vec;
}
