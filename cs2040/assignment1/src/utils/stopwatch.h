#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

public:
    // beign the stopwatch timer
    void start();

    // end the stopwathc timer
    void stop();

    // return elapsed time in miliseconds
    double getElapsedMilliseconds() const;
};

#endif 
