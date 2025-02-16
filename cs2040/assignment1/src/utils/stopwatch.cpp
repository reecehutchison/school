#include "stopwatch.h"

// stopwatch.cpp
// reece hitchison
// sunday feb 16
// function captures the point in time in the real world and stores it as start
// input: nothing
// output: nothing
void Stopwatch::start() {
    startTime=std::chrono::high_resolution_clock::now();
}
// stopwatch.cpp
// reece hutchison
// sunday feb 16
// function captures the point in time in the real world and stores it as end
// input: nothing
// output: nothing
void Stopwatch::stop() {
    endTime=std::chrono::high_resolution_clock::now();
}

// stopwatch.cpp
// reece hutchsion
// sunday feb 16
// will return the difference between the start and end times of the stopwatch
// input: nothing
// output: the diffence between start and end in milliseconds as a type double
double Stopwatch::getElapsedMilliseconds() const {
    std::chrono::duration<double, std::milli> elapsed=endTime-startTime;
    return elapsed.count();
}
