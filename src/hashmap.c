#include "hashmap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SLOTS 512
int hmap_make(struct hash_map* h)
{
    h->node_slots = (struct hash_node**)calloc(HASH_SLOTS, sizeof(struct hash_node*));
    if (!h->node_slots) {
        return NULL;
    }
}
/*
 *  FNV Hash Algorithm
 *  [http://www.isthe.com/chongo/tech/comp/fnv/]
 */
unsigned int hash(const char* key)
{
    unsigned int   keylen = strlen(key);
    unsigned char* p      = (unsigned char *)key;
    unsigned       h      = 0x811c9dc5;
    int            i;

    for (i = 0; i < keylen; i++)
        h = (h ^ p[i]) * 0x01000193;
    return h % HASH_SLOTS;
}
struct hash_node* hnode_make(const char* key, void* data)
{
    struct hash_node* node = (struct hash_node*)malloc(sizeof(struct hash_node));

    node->data = data;
    node->key  = malloc((strlen(key) + 1) * sizeof(char));
    strcpy(node->key, key);
    node->next = NULL;

    return node;
}

struct hash_node* hnode_tail(struct hash_node* node)
{
    struct hash_node* temp = node;
    while (temp->next) {
        temp = temp->next;
    }
    return temp;
}

void hmap_add_key(struct hash_map* h, const char* key, void* data)
{
    int hashed = hash(key);
    if (h->node_slots[hashed] != NULL) {
        struct hash_node* node = hnode_make(key, data);
        struct hash_node* last = hnode_tail(h->node_slots[hashed]);
        last->next             = node;
    } else {
        h->node_slots[hashed] = hnode_make(key, data);
    }
}

bool hmap_has_key(struct hash_map* h, const char* key)
{
    if (!h || !key) {
        return false;
    }
    int hashed = hash(key);

    struct hash_node* node = h->node_slots[hashed];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void* hmap_get(struct hash_map* h, const char* key)
{
    int hashed = hash(key);
    if (h->node_slots[hashed][0].next == NULL)
        return h->node_slots[hashed]->data;

    struct hash_node* head = h->node_slots[hashed];
    if (strcmp(head->key, key) == 0)
        return head->data;

    while (head->next) {
        head = head->next;
        if (strcmp(head->key, key) == 0)
            return head->data;
    }

    return NULL;
}

void hnode_free(struct hash_node* hn)
{
    struct hash_node* current = hn;
    struct hash_node* prev    = NULL;

    while (current) {
        prev    = current;
        current = current->next;

        free(prev);
    }
}

void hmap_free(struct hash_map* h)
{
    for (int i = 0; i < HASH_SLOTS; i++) {
        hnode_free(h->node_slots[i]);
    }
}
