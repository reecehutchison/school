#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define NAMED_PIPE "myPipe"
#define BUFFER_SIZE 99
#define MESSAGE_SIZE 205

int main() {
    
    int fd = open(NAMED_PIPE, O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Client: problem opening pipe");
        return 1;
    }

    printf("~ Client program ~\n");

    char userKey[BUFFER_SIZE]; 
    char passKey[BUFFER_SIZE]; 
    char message[MESSAGE_SIZE];

    while(1) {
        // make the message
        printf("Please enter a user key and a pass key\n");
        
        printf("user key: ");
        if (!fgets(userKey, sizeof(userKey), stdin)) break;
        userKey[strcspn(userKey, "\n")] = '\0';

        printf("pass key: ");
        if (!fgets(passKey, sizeof(passKey), stdin)) break;
        passKey[strcspn(passKey, "\n")] = '\0';

        snprintf(message, sizeof(message), "%s %s", userKey, passKey);

        ssize_t bytesWritten = write(fd, message, strlen(message));
        if (bytesWritten == -1) {
            fprintf(stderr, "Client: failed to write to pipe\n");
            close(fd);
            return 1;
        }

        // message gets sent and now we wait for server to respond
    }

    close(fd);
    return 0;
}