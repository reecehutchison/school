#include "stopwatch.h"

// function captures the point in time in the real world and stores it as start
void Stopwatch::start() {
    startTime=std::chrono::high_resolution_clock::now();
}

// function captures the point in time in the real world and stores it as end
void Stopwatch::stop() {
    endTime=std::chrono::high_resolution_clock::now();
}

// will return the difference between the start and end times of the stopwatch
double Stopwatch::getElapsedMilliseconds() const {
    std::chrono::duration<double, std::milli> elapsed=endTime-startTime;
    return elapsed.count();
}
