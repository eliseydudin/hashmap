#include <stdio.h>
#include <time.h>
#include <hashmap.h>
#include <assert.h>

int main() {
    struct hash_map map;
    hmap_make(&map);

    clock_t msec  = 0;
    int    loops = 1000 * 100;

    for (int i = 0; i < loops; i++) {
        char key[16];
        sprintf(key, "%d", i);
        unsigned int hashed = hash(key);
        char         finalkey[16];
        sprintf(finalkey, "%d", hashed);

        clock_t start = clock(), diff;
        hmap_add_key(&map, finalkey, "data");
        diff = clock() - start;
        msec += diff * 1000 * 1000 / CLOCKS_PER_SEC;
    }

    printf("%lu\n", msec);

    hmap_free(&map);
    return 0;
}
