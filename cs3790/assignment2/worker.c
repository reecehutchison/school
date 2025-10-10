/*
    * Author : Reece Hutchison
    * Date   : Friday, October 10th, 2025
    * 
    * The file contains the worker program for the second assignment
    * for Operating Systems class. The worker will find the prime 
    * numbers from the lower to the upper bound. Lower and upper 
    * bounds are given as command line arguments. 
*/

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define VALID_ARGS 0
#define INVALID_ARG_COUNT 1
#define ARGS_ARE_NOT_NUMBERS 2

#define STRING_IS_NUMBER 0
#define STRING_NOT_NUMBER 1

#define VALID_RANGE 0
#define INVALID_RANGE 1

int validateCommandLineArguments(int argc, char* argv[]);
int stringIsNotNumber(char* ch);
void handleInvalidArgs(int err);
int validateRange(int lowerBound, int upperBound); 

int main(int argc, char* argv[]) {

    int err = validateCommandLineArguments(argc, argv); 
    if (err) {
        handleInvalidArgs(err);
        return err; 
    }
    
    int lowerBound = atoi(argv[1]); 
    int upperBound = atoi(argv[2]);

    err = validateRange(lowerBound, upperBound);
    if (err) {
        fprintf(stderr, "Error: invalid worker range\n");
        return err; 
    }

    printf("lower %d\n", lowerBound);
    printf("upper %d\n", upperBound);


    return 0; 
}

int validateCommandLineArguments(int argc, char* argv[]) {
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
            fprintf(stderr, "Error: invalid arg count for worker, enter an upper and lower bound (ints)\n"); 
            break;

        case ARGS_ARE_NOT_NUMBERS:
            fprintf(stderr, "Error: invalid args for worker, enter an upper and lower bound (ints)\n");
            break;

        default:
            fprintf(stderr, "Error: how did we get here?\n"); 
            break;
    }
}

int validateRange(int lowerBound, int upperBound) {
    if (lowerBound < 1 || lowerBound > upperBound) {
       return INVALID_RANGE; 
    }

    return VALID_RANGE; 
}