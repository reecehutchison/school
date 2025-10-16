#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <openssl/sha.h>

char* sha512_hash(const char *input) {
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

    char* hash = sha512_hash(password);

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
    
    int result = validateUser("passwords.txt", "bob", "bob");
    printf("result : %d\n", result);

    // leave this in!!!! DELETE THIS THO WHEN DONE!
    // TODO: go make it print the val in the fib.c...
    printf("fib numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89");
    

    return 0; 
}