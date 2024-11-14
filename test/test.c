#include <hashmap.h>
#include <assert.h>

int main() {
    struct hash_map map;
    hmap_make(&map);

    const char* key  = "key";
    char* data = "DATA_1";
    hmap_add_key(&map, key, data);

    assert((char *)hmap_get(&map, "key") == data);
    assert(!hmap_has_key(&map, "no-exist"));

    hmap_free(&map);
    return 0;
}
