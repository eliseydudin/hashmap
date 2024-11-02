#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char* argv[])
{
    struct hash_map my_hash = { 0 };
    printf("Testing cases\n");
    hmap_make(&my_hash);
    printf("[SUCCESS] Hash created\n");
    const char* key  = "key";
    char*       data = "DATA_1";
    hmap_add_key(&my_hash, key, data);
    printf("[SUCCESS] Added %s to %s\n", "DATA_1", "key");
    bool key_exists = hmap_has_key(&my_hash, "no-exist");
    if (key_exists) {
        printf("Key: %s found\n", key);
    } else {
        printf("Key: %s not found\n", key);
    }
    bool key_exists2 = hmap_has_key(&my_hash, key);
    if (key_exists2) {
        printf("Key: %s found\n", key);
    } else {
        printf("Key: %s not found\n", key);
    }
    double msec  = 0;
    int    loops = 1000 * 100;

    for (int i = 0; i < loops; i++) {
        char key[16];
        sprintf(key, "%d", i);
        unsigned int hashed = hash(key);
        char         finalkey[16];
        sprintf(finalkey, "%d", hashed);

        clock_t start = clock(), diff;
        hmap_add_key(&my_hash, finalkey, "data");
        diff = clock() - start;
        msec += diff * 1000 * 1000 / CLOCKS_PER_SEC;
    }
    printf("done adding keys (%lf ns) at %lf ns avg\n", msec, (double)msec / (double)loops);
    char key2[3]     = "123";
    bool key_exists3 = hmap_has_key(&my_hash, key2);
    if (key_exists2) {
        printf("Key: %s found\n", key2);
    } else {
        printf("Key: %s not found\n", key2);
    }
    return EXIT_SUCCESS;
}
