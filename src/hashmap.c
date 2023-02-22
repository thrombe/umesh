

#include "hashmap.h"
#include "linked_list.h"
#include "keyvalue.h"
#include "helpers.h"
#include<stdlib.h>
#include<stdio.h>


HashMap new_hashmap() {
    HashMap m;
    // m.size = 421;
    m.size = 41;
    m.data = malloc(sizeof(LinkedList)*m.size);
    for (int i=0; i<m.size; i++) {
        m.data[i] = new_llist();
    }
    return m;
}

// https://stackoverflow.com/a/7666577
int hash(void* data, int width) {
    char* str = (char*)data;
    int hash = 5381;

    for (int i=0; i<width; i++) {
        int c = (int)str[i];
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int hash_key(Key* key) {
    return hash(key->key, key->key_width);
}

int get_index(HashMap* m, Key* k) {
    int h = hash(k->key, k->key_width);
    h %= m->size;
    h += m->size; // -ve mod :/
    h %= m->size;
    return h;
}

bool key_match(Key* k1, Key* k2) {
    if (k1->key_width != k2->key_width) {
        return false;
    } else {
        for (int i=0; i<k1->key_width; i++) {
            if (k1->key[i] != k2->key[i]) {
                return false;
            }
        }
        
        return true;
    }
}

KeyValue* get_item_hashmap(HashMap* m, Key* k) {
    int i = get_index(m, k);
    LinkedList* ll = &(m->data[i]);
    Node* n = ll->first;
    while (n != NULL) {
        if (key_match(&(n->val.key), k)) {
            return &(n->val);
        }
        n = n->next;
    }
    return NULL;
}

void insert_element_hashmap(HashMap* m, KeyValue kv) {
    int h = get_index(m, &(kv.key));
    LinkedList* ll = &(m->data[h]);
    KeyValue* dest_kv = get_item_hashmap(m, &(kv.key));
    if (dest_kv == NULL) {
        insert_at_front_ll(ll, kv);
    } else {
        free_keyvalue(dest_kv);
        *dest_kv = kv;
    }
}

bool delete_item_hashmap(HashMap* m, Key* k) {
    int i = get_index(m, k);
    LinkedList* ll = &(m->data[i]);
    Node** p = &(ll->first);
    Node* n = ll->first;
    while (n != NULL) {
        if (key_match(&(n->val.key), k)) {
            *p = n->next;
            n->next = NULL;
            free_node(n);
            return true;
        }
        p = &(n->next);
        n = n->next;
    }
    return false;
}

void print_hashmap(HashMap* m) {
    printf("---\n");
    for (int i=0; i<m->size; i++) {
        printf(" |-> ");
        print_llist(&(m->data[i]));
    }
    printf("---\n");
}

void free_hashmap(HashMap* m) {
    if (m != NULL) {
        for (int i=0; i<m->size; i++) {
            free_llist(&(m->data[i]));
        }
        free(m->data);
        m->data = NULL;
        m->size = 0;
    }
}
