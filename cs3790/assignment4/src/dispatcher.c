#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define PROG_COUNT 3
#define SLEEP_TIME 2

int main() {
    
    pid_t pids[PROG_COUNT];

    for (int i = 0; i < PROG_COUNT; i++) {
        pid_t pid = fork(); 

        if (pid == -1) {
            fprintf(stderr, "ERROR : disp : problem forking child");
            
            return 1; 
        } else if (pid == 0) {
            char arg[2];      
            arg[0] = 'a' + i; 
            arg[1] = '\0';

            int err = execl("./bin/prog", "./bin/prog", arg, (char *)NULL);

            if (err) {
                fprintf(stderr, "ERROR : disp : problem executing child\n");
                return 1; 
            }
        } else {
            pids[i] = pid; 
            kill(pids[i], SIGSTOP);
        }
    }

    while (1) {
        for (int i = 0; i < PROG_COUNT; i++) {
            kill(pids[i], SIGCONT);  
            sleep(SLEEP_TIME);                
            kill(pids[i], SIGSTOP);  
        }
    }

    // no need to wait for cleanup, just end with Ctrl+C
    return 0; 
}