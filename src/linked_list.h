
#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER


#include "keyvalue.h"
#include "helpers.h"


typedef struct Node {
    struct Node* next;
    KeyValue val;
} Node; // !Copy


typedef struct {
    Node* first;
} LinkedList; // Copy


void free_node(Node* n);
void print_node(Node* n);
LinkedList new_llist();
bool insert_at_position_ll(LinkedList* a, int pos, KeyValue element);
void insert_at_front_ll(LinkedList* a, KeyValue kv);
void print_llist(LinkedList* a);
void free_llist(LinkedList* a);


#endif // LINKEDLIST_HEADER
