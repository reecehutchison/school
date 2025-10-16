#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define MESSAGE_SIZE 205

#define FIFO_CS "client_to_server"
#define FIFO_SC "server_to_client"

int main() {
    
    int fdWrite = open(FIFO_CS, O_WRONLY);
    if (fdWrite == -1) {
        fprintf(stderr, "Client: error open write\n");
        return 1;
    }

    int fdRead = open(FIFO_SC, O_RDONLY);
    if (fdRead == -1) {
        fprintf(stderr, "Client: error open read\n");
        close(fdWrite);
        return 1;
    }

    printf("~ Client program ~\n");

    char userKey[BUFFER_SIZE]; 
    char passKey[BUFFER_SIZE]; 
    char message[MESSAGE_SIZE];
    char buffer[BUFFER_SIZE];


    // main client loop
    while(1) {
        // get user input
        printf("--------------------------------------\n");
        printf("Please enter a user key and a pass key\n");

        printf("user key: ");
        if (!fgets(userKey, sizeof(userKey), stdin)) break;
        userKey[strcspn(userKey, "\n")] = '\0';

        printf("pass key: ");
        if (!fgets(passKey, sizeof(passKey), stdin)) break;
        passKey[strcspn(passKey, "\n")] = '\0';

        // send USER command to server
        snprintf(message, sizeof(message), "USER %s %s", userKey, passKey);

        ssize_t bytesWritten = write(fdWrite, message, strlen(message));
        if (bytesWritten == -1) {
            fprintf(stderr, "Client: failed to write to pipe\n");

            return 1;
        }

        // wait for server response
        ssize_t bytesRead = read(fdRead, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("Server response: %s\n", buffer);

            // if valid login, let user enter commands
            if (strncmp(buffer, "+ACCOUNT VALID", 14) == 0) {
                printf("Enter EXEC command (e.g., EXEC fib 5): ");
                char command[MESSAGE_SIZE];

                if (fgets(command, sizeof(command), stdin)) {
                    command[strcspn(command, "\n")] = '\0';
                    ssize_t cmdWritten = write(fdWrite, command, strlen(command));
                    
                    if (cmdWritten == -1) {
                        fprintf(stderr, "Client: failed to write command\n");
                    }
                }
            } else {
                printf("Client: invalid user key or pass key\n");
            }
        } else {
            printf("Client: no response from server\n");
        }
    }

    close(fdRead);
    close(fdWrite);
    
    return 0;
}