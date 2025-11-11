#include <stdio.h>
#include <unistd.h>

#define SLEEP_TIME 1 // unit is seconds

int main(int argc, char *argv[]) {    
    if (argc != 2) {
        fprintf(stderr, "ERROR : prog : must run prog with 1 arg");
        
        return 1; 
    }
   
    while (1) {
        fprintf(stdout, "%s\n", argv[1]);
        sleep(SLEEP_TIME);
    }
            
    return 0; 
}