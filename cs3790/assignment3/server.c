#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>         


#define FIFO_CS "client_to_server"
#define FIFO_SC "server_to_client"

char* sha512Hash(const char *input) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    char* hash_hex = malloc(SHA512_DIGEST_LENGTH * 2 + 1);

    if (!hash_hex) return NULL;  

    SHA512((const unsigned char*)input, strlen(input), hash);

    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        sprintf(&hash_hex[i * 2], "%02x", hash[i]);

    hash_hex[SHA512_DIGEST_LENGTH * 2] = '\0';
    return hash_hex;
}

int validateUser(char* filename, char* password, char* passKey) {
    FILE *file = fopen(filename, "r"); 
    if (!file) {
        fprintf(stderr, "Server: failed to open file\n");
        return 0;
    }

    char key[256];
    char val[1024];

    char* hash = sha512Hash(password);

    while (fgets(key, sizeof(key), file) && fgets(val, sizeof(val), file)) {
        // remove newlines
        key[strcspn(key, "\n")] = 0;
        val[strcspn(val, "\n")] = 0;

        if (strcmp(hash, val) == 0 && strcmp(key, passKey) == 0) {
            fclose(file);
            free(hash);

            return 1; 
        }
    }

    free(hash);
    fclose(file);
    return 0;
}

int main() {
    printf("Server running:\n");
    printf("fib numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89\n");

    // flush old pipes
    unlink(FIFO_CS);
    unlink(FIFO_SC);

    int err = mkfifo(FIFO_CS, 0666);
    if (err && errno != EEXIST) { 
        fprintf(stderr, "Server: mkfifo failed");
        return 1; 
    }

    err = mkfifo(FIFO_SC, 0666);
    if (err && errno != EEXIST) { 
        fprintf(stderr, "Server: mkfifo failed");
        return 1; 
    }

    int fdRead = open(FIFO_CS, O_RDONLY | O_NONBLOCK);
    if (fdRead == -1) {
        fprintf(stderr, "Server: read open failed");
        return 1;
    }

    int fdWrite = open(FIFO_SC, O_WRONLY);
    if (fdWrite == -1) {
        fprintf(stderr, "Server: write open failed");
        return 1;
    }

    // main server loop
    char buffer[256];
    while (1) {
        // read from client pipe
        ssize_t bytesRead = read(fdRead, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            printf("-------------------------------\n");
            buffer[bytesRead] = '\0';
            buffer[strcspn(buffer, "\n")] = 0;
            printf("Received from client: %s\n", buffer);
        } else {
            continue;
        }

        char user[128];
        char pass[256];

        // get USER command from client
        char command[64];
        if (sscanf(buffer, "%63s %127s %255s", command, user, pass) == 3 && strcmp(command, "USER") == 0) {
            printf("Server: parsed USER command user='%s', pass='%s'\n", user, pass);
            
            int ok = validateUser("passwords.txt", pass, user);
            
            if (ok) {
                printf("Server: +ACCOUNT VALID\n");
                
                write(fdWrite, "+ACCOUNT VALID\n", strlen("+ACCOUNT VALID\n"));

                // user command loop
                while (1) {
                    ssize_t bytesRead = read(fdRead, buffer, sizeof(buffer) - 1);
                    
                    if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    buffer[strcspn(buffer, "\n")] = 0;
                    
                    printf("Received command: %s\n", buffer);

                    // check if command starts with EXEC
                    char *token = strtok(buffer, " ");

                    if (token && strcmp(token, "EXEC") == 0) {
                        printf("Server: executing EXEC command\n");

                        // get the program name
                        token = strtok(NULL, " ");
                        if (token) {
                            // fork and exec the program
                            if (fork() == 0) {
                                char *args[10];
                                char path[256];
                                snprintf(path, sizeof(path), "./targets/%s", token);
                                args[0] = path;
                                int i = 1;

                                while ((token = strtok(NULL, " ")) && i < 9) {
                                    args[i++] = token;
                                }
                                args[i] = NULL;
                                execv(path, args);

                                exit(1);
                            } else {
                                wait(NULL);
                            }
                        } else {
                            printf("Server: no program specified\n");
                        }
                    } else {
                        printf("Server: unknown command\n");
                    }
                    break;
                    }
                }
                continue;

            } else {
                printf("Server: -INVALID ACCOUNT. +GOODBYE\n");
                write(fdWrite, "-INVALID ACCOUNT.\n+GOODBYE\n", strlen("-INVALID ACCOUNT.\n+GOODBYE\n"));
            }
        } else {
            printf("Server: unsupported message: %s\n", buffer);
            write(fdWrite, "-INVALID ACCOUNT.\n+GOODBYE\n", strlen("-INVALID ACCOUNT.\n+GOODBYE\n"));
        }
    }

    return 0; 
}