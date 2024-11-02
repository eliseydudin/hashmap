#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <stdbool.h>
#define HASH_SLOTS 512

struct hash_map {
  struct hash_node **node_slots;
};

struct hash_node {
  void *data;
  char *key;
  struct hash_node *next;
};

unsigned int hash(const char *key);

void hmap_make(struct hash_map *h);
void hmap_free(struct hash_map *h);
void hmap_add_key(struct hash_map *h, const char *key, void *data);
void *hmap_get(struct hash_map *h, const char *key);
bool hmap_has_key(struct hash_map *h, const char *key);

void hnode_free(struct hash_node *hn);
struct hash_node *hnode_make(const char *key, void *data);
struct hash_node *hnode_detect_cycle(struct hash_node *hn);
struct hash_node *hnode_tail(struct hash_node *hn);
#endif
