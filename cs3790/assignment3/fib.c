#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* isNumber(char* str) {
    if (strlen(str) == 0) {
        return "Fib: arg must be non empty";
    }

    if (*str == '-') {
        return "Fib: arg must be a positive number";
    }

    while (*str) {
        if (!isdigit(*str)) {
            return "Fib: arg must be a number";
        }

        str++; 
    }

    return NULL;
}

int computeFib(int n) {
    if (n == 0) {
        return 0;
    } else if(n == 1) {
        return 1;
    } 

    return computeFib(n - 1) + computeFib(n - 2);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Fib: enter only 1 arg\n");
        return 1;
    }
    
    char* arg = argv[1];

    char* err = isNumber(arg);
    if (err) {
        fprintf(stderr, "%s\n", err);
        return 1;
    }

    int n = atoi(arg);

    if (n > 12) {
        fprintf(stderr, "Fib: only aloud values less then 12");
    }

    int fibVal = computeFib(n);
    printf("(%d) fib val: %d\n",n, fibVal);
    
    return 0;
}