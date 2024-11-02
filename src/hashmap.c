#include "hashmap.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SLOTS 512
void hmap_make(struct hash_map* h)
{
    h->node_slots = (struct hash_node**)calloc(HASH_SLOTS, sizeof(struct hash_node*));
    if (!h->node_slots) {
        printf("[ERROR] could not allocate memory for hashmap slots");
        exit(EXIT_FAILURE);
    }
}
/*
 *  FNV Hash Algorithm
 *  [http://www.isthe.com/chongo/tech/comp/fnv/]
 */
unsigned int hash /*naive*/ (const char* key)
{
    unsigned char* p = key;
    unsigned       h = 0x811c9dc5;
    int            i;

    for (i = 0; i < HASH_SLOTS; i++)
        h = (h ^ p[i]) * 0x01000193;

    return h;
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

void* hmap_get(struct hash_map* h, const char* key)
{
    int hashed = hash(key);
    if (h->node_slots[hashed][0].next != NULL) {
        struct hash_node* head = h->node_slots[hashed];
        if (strcmp(head->key, key) == 0) {
            return head->data;
        } else {
            while (head->next) {
                head = head->next;
                if (strcmp(head->key, key) == 0) {
                    return head->data;
                }
            }
            return NULL;
        }
    } else {
        return h->node_slots[hashed]->data;
    }
}

struct hash_node* hnode_detect_cycle(struct hash_node* hn)
{
    struct hash_node* one_step_pointer = hn;
    struct hash_node* two_step_pointer = hn;
    while (true) {
        one_step_pointer = one_step_pointer->next;
        if (!two_step_pointer->next)
            return NULL;
        two_step_pointer = two_step_pointer->next->next;
        if (!one_step_pointer || !two_step_pointer)
            return NULL;

        if (one_step_pointer == two_step_pointer)
            return one_step_pointer;
    }
}

void hnode_free(struct hash_node* hn)
{
    struct hash_node* current = hn;
    struct hash_node* prev    = NULL;

    struct hash_node* cycle_location = hnode_detect_cycle(hn);
    while (current) {
        prev    = current;
        current = current->next;
        if (prev == cycle_location)
            prev->next = NULL;
        else {
            free(prev);
        }
    }
}

void hmap_free(struct hash_map* h)
{
    for (int i = 0; i < HASH_SLOTS; i++) {
        hnode_free(h->node_slots[i]);
    }
}
