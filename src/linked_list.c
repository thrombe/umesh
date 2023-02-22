
#include "keyvalue.h"
#include "linked_list.h"
#include "helpers.h"
#include<stdlib.h>
#include<stdio.h>

// recursive
void free_node(Node* n) {
    if (n != NULL) {
        free_keyvalue(&(n->val));
        free_node(n->next);
        n->next = NULL;
        free(n);
    }
}

void print_node(Node* n) {
    if (n == NULL) {
        return;
    }
    print_keyvalue(&(n->val));
}



LinkedList new_llist() {
    LinkedList a;
    a.first = NULL;
    return a;
}

bool insert_at_position_ll(LinkedList* a, int pos, KeyValue element) {
    if (pos < 1) {
        return false;
    }
    int index = pos - 1;

    Node* b = a->first;
    if (b == NULL) {
        if (index != 0) {
            return false;
        }
        a->first = malloc(sizeof(Node));
        a->first->val = element;
        a->first->next = NULL;
        return true;
    }

    if (index == 0) {
        b = malloc(sizeof(Node));
        b->val = element;
        b->next = a->first;
        a->first = b;
        return true;
    }

    for (int i=1; i<index; i++) {
        if (b->next == NULL) {
            return false;
        }
        b = b->next;
    }

    Node* c = malloc(sizeof(Node));
    c->next = b->next;
    c->val = element;
    b->next = c;
    return true;
}

void insert_at_front_ll(LinkedList* a, KeyValue kv) {
    insert_at_position_ll(a, 1, kv);
}

void print_llist(LinkedList* a) {
    printf("[ ");
    Node* b = a->first;
    while (b != NULL) {
        printf("-> ");
        print_node(b);
        b = b->next;
    }
    printf("]\n");
}

void free_llist(LinkedList* a) {
    if (a != NULL) {
        free_node(a->first);
        a->first = NULL;
    }
}

