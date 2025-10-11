/*
    * Author : Reece Hutchison
    * Date   : Friday, October 10th, 2025
    * 
    * This file contains the boss program for the 2nd assignment
    * in Operating Systems class. It takes a worker count (int), 
    * and an upper bound integer argument. The workers will find the
    * primes, in their specific range, and in total all the primes from
    * 0 to the upper bound given input will be printed to the std out. 
*/

#include <stdio.h>
#include <stdlib.h>  
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define VALID_ARGS 0
#define INVALID_ARG_COUNT 1
#define ARGS_ARE_NOT_NUMBERS 2

#define STRING_IS_NUMBER 0
#define STRING_NOT_NUMBER 1

#define UPPER_BOUND_LIMIT 9999
#define UPPER_LIMIT_ERR 9

#define UPPER_STR_SIZE 99

#define NOT_ENOUGH_WORKERS 1
#define UPPER_BOUND_EXCEEDS_WORKERS 2
#define NOT_LARGE_ENOUGH_UPPER 3

int validateArgs(int argc, char* argv[]);
int stringIsNotNumber(char* ch);
void handleInvalidArgs(int err);
int validateNums(int numWorkers, int upperBound);
void ensureOutputDir();


int main(int argc, char* argv[]) {
    int err = validateArgs(argc, argv);
    if (err) {
        handleInvalidArgs(err);
        return err; 
    }

    int numWorkers = atoi(argv[1]);
    int upperBound = atoi(argv[2]);

    err = validateNums(numWorkers, upperBound);
    if (err) {
        return err; 
    }

    ensureOutputDir();

    int rangeSize = upperBound / numWorkers;

    for (int i = 0; i < numWorkers; i++) {
        int lower = (i * rangeSize) + 1; 
        if (lower < 2) {
            lower = 2;
        }

        int upper = (i == numWorkers - 1) ? upperBound : (i + 1) * rangeSize;

        if (lower > upper) {  // skip invalid worker ranges
            continue;
        }

        int pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            char lowerStr[UPPER_STR_SIZE];
            char upperStr[UPPER_STR_SIZE];
            snprintf(lowerStr, sizeof(lowerStr), "%d", lower);
            snprintf(upperStr, sizeof(upperStr), "%d", upper);

            execl("./targets/worker", "./targets/worker", lowerStr, upperStr, (char*)NULL);
            perror("execl failed"); // in case execl fails
            exit(1);
        }
    }

    for (int i = 0; i < numWorkers; i++) {
        wait(NULL);
    }
    
    return 0; 
}

int validateArgs(int argc, char* argv[]) {
    if (argc != 3) {
        return INVALID_ARG_COUNT; 
    }

    if (stringIsNotNumber(argv[1]) || stringIsNotNumber(argv[2])) {
        return ARGS_ARE_NOT_NUMBERS;
    }

    return VALID_ARGS;
}

int stringIsNotNumber(char* ch) {
    if (*ch == '\0') {
        return STRING_NOT_NUMBER;
    }
    
    while (*ch != '\0') {
        if (*ch < '0' || *ch > '9') {
            return STRING_NOT_NUMBER;
        }

        ch++; 
    }

    return STRING_IS_NUMBER;
}

void handleInvalidArgs(int err) {
    switch (err) {
        case INVALID_ARG_COUNT:
            fprintf(stderr, "Error: boss received invalid amount of arguments (need 2 ints)\n");
            break;
        
        case ARGS_ARE_NOT_NUMBERS:
            fprintf(stderr, "Error: boss received a non number argument or negative\n"); 
            break; 
        
        default:
            fprintf(stderr, "Error: how did we get here?\n"); 
            break;
        }
}

int validateNums(int numWorkers, int upperBound) {
    if (numWorkers < 1) {
        fprintf(stderr, "Error: boss number of workers not above 1\n");
        return NOT_ENOUGH_WORKERS; 
    }

    if (upperBound > UPPER_BOUND_LIMIT) {
        fprintf(stderr, "Error: upper bound given to boss is above the limit\n");
        return UPPER_LIMIT_ERR;
    }

    if (upperBound < 2) {
        fprintf(stderr, "Error: boss upper bound should be larger than 1\n");
        return NOT_LARGE_ENOUGH_UPPER;
    }

    if (numWorkers > upperBound - 1) {
        fprintf(stderr, "Error: num of workers should not exceed upper bound\n");
        return UPPER_BOUND_EXCEEDS_WORKERS; 
    }

    return VALID_ARGS;
}

void ensureOutputDir() {
    struct stat st = {0};
    if (stat("./outputs", &st) == -1) {
        mkdir("./outputs", 0700);
    }
}