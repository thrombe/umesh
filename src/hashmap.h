
#ifndef HASHMAP_HEADER
#define HASHMAP_HEADER


#include "linked_list.h"
#include "keyvalue.h"
#include "helpers.h"


typedef struct {
    LinkedList* data;
    int size;
} HashMap; // Copy


HashMap new_hashmap();
int hash(void* data, int width);
int hash_key(Key* key);
int get_index(HashMap* m, Key* k);
bool key_match(Key* k1, Key* k2);
KeyValue* get_item_hashmap(HashMap* m, Key* k);
void insert_element_hashmap(HashMap* m, KeyValue kv);
bool delete_item_hashmap(HashMap* m, Key* k);
void print_hashmap(HashMap* m);
void free_hashmap(HashMap* m);


#endif // HASHMAP_HEADER

