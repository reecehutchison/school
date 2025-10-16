#include <stdio.h>
#include <stdlib.h>        
#include <string.h>         
#include <openssl/sha.h>   
#include <errno.h>   
#include <sys/stat.h>      
#include <fcntl.h>          
#include <unistd.h>         


#define NAMED_PIPE "myPipe"

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

    int err = mkfifo(NAMED_PIPE, 0666);
    if (err && errno != EEXIST) { 
        fprintf(stderr, "Server: mkfifo failed");
        return 1; 
    }

    int fd = open(NAMED_PIPE, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Server: open failed");
        return 1;
    }

    // server loop
    char buffer[256];
    while (1) {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
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

        if (sscanf(buffer, "%127s %255s", user, pass) == 2) {
            printf("Server: parsed user='%s', pass='%s'\n", user, pass);
            int ok = validateUser("passwords.txt", pass, user);
            if (ok) {
                printf("Server: +ACCOUNT VALID\n");
            } else {
                printf("Server: -INVALID ACCOUNT. +GOODBYE\n");
            }
        } else {
            printf("Server: bad or unsupported message: %s\n", buffer);
        }
    }

    return 0; 
}