/*
    * Author : Reece Hutchison
    * Date   : Friday, October 10th, 2025
    * 
    * The file contains the worker program for the second assignment
    * for Operating Systems class. The worker will find the prime 
    * numbers from the lower to the upper bound. Lower and upper 
    * bounds are given as command line arguments. 
*/

// -- CHANGE THIS FOR DIFFERENT MODES! -- // 
// WRITE TO JUST STD OUT == 0
// WRITE TO FILE MODE AND STD OUT == 1
#define OUTPUT_MODE 1
// ------------------------------------- //

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0

#define VALID_ARGS 0
#define INVALID_ARG_COUNT 1
#define ARGS_ARE_NOT_NUMBERS 2

#define STRING_IS_NUMBER 0
#define STRING_NOT_NUMBER 1

#define VALID_RANGE 0
#define INVALID_RANGE 1

typedef struct ListNode {
    int val; 
    struct ListNode* next; 
} ListNode; 

typedef struct List {
    ListNode* head; 
    ListNode* tail; 
} List; 

List* findPrimes(int lowerBound, int UpperBound);
int validateCommandLineArguments(int argc, char* argv[]);
int stringIsNotNumber(char* ch);
void handleInvalidArgs(int err);
int validateRange(int lowerBound, int upperBound); 
List* createList();
void append(List* list, int newVal);
void freeList(List* list);
void writePrimeToFile(int lower, int upper, int prime);

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

    List* primes = findPrimes(lowerBound, upperBound);
     
    ListNode* curr = primes->head; 
    printf("primes: "); 
    while (curr != NULL) {
        printf("%d ", curr->val);

        if (OUTPUT_MODE) {
            writePrimeToFile(lowerBound, upperBound, curr->val);
        }

        curr = curr->next; 
    }
    printf("\n");

    freeList(primes); 

    return 0; 
}

List* findPrimes(int lowerBound, int upperBound) {
    List* primes = createList(); 
    int n = upperBound + 1;
    int seen[n];

    seen[0] = TRUE;
    seen[1] = TRUE; 

    for (int i = 2; i < n; i++) {
        seen[i] = FALSE; 
    }

    for (int i = 2; i < n; i++) {
        if (seen[i]) {
            continue; 
        }

        int prime = i; 
        
        if (prime >= lowerBound && prime <= upperBound) {
            append(primes, prime); 
        }

        for (int j = prime * prime; j < n; j += prime) {
            seen[j] = TRUE; 
        }
    }
    
    return primes;
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
    if (lowerBound < 2 || lowerBound > upperBound) {
       return INVALID_RANGE; 
    }

    return VALID_RANGE; 
}

List* createList() {
    List* newList = malloc(sizeof(List)); 
    newList->head = NULL; 
    newList->tail = NULL; 

    return newList;
}

void append(List* list, int newVal) {
    ListNode* newListNode = malloc(sizeof(ListNode)); 
    newListNode->next = NULL; 
    newListNode->val = newVal; 
    
    if (list->head == NULL) {
        list->head = newListNode;
        list->tail = newListNode; 
    } else {
        list->tail->next = newListNode; 
        list->tail = newListNode; 
    }
}

void freeList(List* list) {
    ListNode* curr = list->head;

    while (curr != NULL) {
        ListNode* tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    free(list);
}

void writePrimeToFile(int lower, int upper, int prime) {
    char filename[100];
    snprintf(filename, sizeof(filename), "./outputs/primes_%d_%d.txt", lower, upper);
    
    FILE *fp = fopen(filename, "a");  
    if (fp == NULL) {
        perror("Failed to open output file");
        return;
    }
    
    fprintf(fp, "%d ", prime);
    fclose(fp);
}