

#include "keyvalue.h"
#include "helpers.h"
#include<stdlib.h>
#include<stdio.h>


// pointer takes ownership
Key new_key(char* key, int key_width) {
    Key k;
    k.key = key;
    k.key_width = key_width;
    return k;
}

// takes in null-terminated string
Key new_key_copied(char* key) {
    return new_key(heap_str(key), str_len(key));
}

void print_key(Key* k) {
    print_str(k->key, k->key_width);
}

void free_key(Key* k) {
    if (k != NULL) {
        free(k->key);
        k->key = NULL;
        k->key_width = 0;
    }
}



void print_keyvalue(KeyValue* kv) {
    if (kv == NULL) {
        return;
    }

    printf("\"");
    print_key(&(kv->key));
    printf("\": ");

    printf("\"");
    printf("%ld", kv->value);
    printf("\" ");
}

// takes ownership of both pointers
KeyValue new_keyvalue(char* key, int key_width, void* value, int value_width) {
    KeyValue kv;
    kv.key = new_key(key, key_width);

    kv.value = value;
    kv.value_width = value_width;
    return kv;
}

KeyValue clone_keyvalue(KeyValue* kv) {
    char* key = malloc(sizeof(char)*kv->key.key_width);
    for (int i=0; i<kv->key.key_width; i++) {
        key[i] = kv->key.key[i];
    }

    void* value = malloc(kv->value_width);
    char* source_val = (char*)(kv->value);
    char* temp_val = (char*)value; // for alignment maybe
    for (int i=0; i<kv->value_width; i++) {
        temp_val[i] = source_val[i];
    }
    
    KeyValue kv2;

    kv2.key.key = key;
    kv2.key.key_width = kv->key.key_width;

    kv2.value = value;
    kv2.value_width = kv->value_width;
    return kv2;
}

void free_keyvalue(KeyValue* kv) {
    if (kv != NULL) {
        free_key(&(kv->key));
        free(kv->value);
        kv->value = NULL;
        kv->value_width = 0;
    }
}
