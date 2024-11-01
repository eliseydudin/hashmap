#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SLOTS 512
struct hash_map {
    struct hash_node** node_slots;
};

struct hash_node {
    uint32_t          data;
    char*             key;
    struct hash_node* next;
};

void hash_map_create(struct hash_map* h)
{
    h->node_slots = (struct hash_node**)calloc(HASH_SLOTS, sizeof(struct hash_node*));
    if (!h->node_slots) {
        printf("[ERROR] could not allocate memory for hashmap slots");
        exit(EXIT_FAILURE);
    }
}
int hash /*naive*/ (const char* key)
{
    int key_length = strlen(key);
    int sum        = 0;
    for (int i = 0; i < key_length; i++) {
        sum += (int)key[i];
    }
    return sum % HASH_SLOTS;
}
struct hash_node* make_node(const char* key, int data)
{
    struct hash_node* node = (struct hash_node*)malloc(sizeof(struct hash_node));

    node->data = data;
    node->key  = malloc((strlen(key) + 1) * sizeof(char));
    strcpy(node->key, key);
    node->next = NULL;

    return node;
}

struct hash_node* get_last_node(struct hash_node* node)
{
    struct hash_node* temp = node;
    while (temp->next) {
        temp = temp->next;
    }
    return temp;
}

void hash_insert_key(struct hash_map* h, const char* key, int data)
{
    int hashed = hash(key);
    if (h->node_slots[hashed] != NULL) {
        struct hash_node* node = make_node(key, data);
        struct hash_node* last = get_last_node(h->node_slots[hashed]);
        last->next             = node;
    } else {
        h->node_slots[hashed] = make_node(key, data);
    }
}

int hash_get(struct hash_map* h, const char* key)
{
    int hashed = hash(key);
    int data;
    if (h->node_slots[hashed][0].next != NULL) {
        struct hash_node* head = h->node_slots[hashed];
        if (strcmp(head->key, key) == 0) {
            data = head->data;
        } else {
            while (head->next) {
                head = head->next;
                if (strcmp(head->key, key) == 0) {
                    data = head->data;
                    break;
                }
            }
        }
    } else {
        data = h->node_slots[hashed]->data;
    }
    printf("\n%s %d\n", key, data);
    return data;
}

void run_insert_key_tests(struct hash_map* h)
{
    hash_insert_key(h, "apple", 45);
    hash_insert_key(h, "banana", 23);
    hash_insert_key(h, "grape", 12);
    hash_insert_key(h, "peach", 88);
    hash_insert_key(h, "melon", 37);
    hash_insert_key(h, "lemon", 56);
    hash_insert_key(h, "berry", 74);
    hash_insert_key(h, "mango", 5);
    hash_insert_key(h, "kiwi", 49);
    hash_insert_key(h, "plum", 30);
    hash_insert_key(h, "cherry", 91);
    hash_insert_key(h, "orange", 67);
    hash_insert_key(h, "papaya", 82);
    hash_insert_key(h, "peanut", 14);
    hash_insert_key(h, "carrot", 27);
    hash_insert_key(h, "radish", 60);
    hash_insert_key(h, "spinach", 21);
    hash_insert_key(h, "cabbage", 11);
    hash_insert_key(h, "tomato", 92);
    hash_insert_key(h, "potato", 15);
    hash_insert_key(h, "zucchini", 76);
    hash_insert_key(h, "asparagus", 34);
    hash_insert_key(h, "broccoli", 59);
    hash_insert_key(h, "cauliflower", 48);
    hash_insert_key(h, "artichoke", 73);
    hash_insert_key(h, "eggplant", 9);
    hash_insert_key(h, "radicchio", 26);
    hash_insert_key(h, "cucumber", 68);
    hash_insert_key(h, "onion", 33);
    hash_insert_key(h, "bellpepper", 84);
    hash_insert_key(h, "ginger", 32);
    hash_insert_key(h, "turmeric", 77);
    hash_insert_key(h, "cilantro", 50);
}

int main(int argc, char* argv[])
{
    struct hash_map my_hash = { 0 };
    hash_map_create(&my_hash);
    run_insert_key_tests(&my_hash);
    int value = hash_get(&my_hash, "eggplant");
    return EXIT_SUCCESS;
}
