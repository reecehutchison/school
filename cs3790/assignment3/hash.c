#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>

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

int main(void) {
    const char* password = "apple";
    char* hash = sha512_hash(password);

    printf("key  : '%s'\n", password);
    printf("hash : '%s'\n", hash);
    free(hash);

    return 0;
}
