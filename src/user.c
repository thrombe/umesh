

#include "hashmap.h"
#include "user.h"
#include "keyvalue.h"
#include "helpers.h"
#include "stack.h"
#include<stdlib.h>
#include<stdio.h>


User* new_user() {
    User* u = malloc(sizeof(User));

    u->undo_stack = new_stack();
    u->redo_stack = new_stack();

    u->data = new_hashmap();
    return u;
}

void print_user(User* u) {
    if (u == NULL) {
        printf("error: user is NULL\n");
        return;
    }
    printf("undo: ");
    print_stack(&(u->undo_stack));
    printf("redo: ");
    print_stack(&(u->redo_stack));
    
    printf("data: [\n");
    for (int i=0; i<u->data.size; i++) {
        LinkedList* ll = &(u->data.data[i]);
        Node* n = ll->first;
        while (n != NULL) {
            printf("    \"");
            print_key(&(n->val.key));
            printf("\": \"");
            print_str((char*)(n->val.value), n->val.value_width);
            printf("\"\n");
            n = n->next;
        }
    }
    printf("]\n");
}

void reset_redo_stack(User* u) {
    StackResult r = pop_stack(&(u->redo_stack));
    while (r.err == false) {
        free_keyvalue(&(r.ok.kv));
        r = pop_stack(&(u->redo_stack));
    }
}

// overwrites if key collides
void insert_keyvalue(User* u, KeyValue kv) {
    Operation o;
    o.opcode = OP_add;
    o.kv = clone_keyvalue(&kv);
    reset_redo_stack(u);
    push_stack(&(u->undo_stack), o);
    insert_element_hashmap(&(u->data), kv);
}

// takes 2 numm-terminated strings
void insert_keyvalue_copied(User* u, char* key, char* value) {
    insert_keyvalue(u, new_keyvalue(heap_str(key), str_len(key), (void*)(heap_str(value)), str_len(value)));
}

KeyValue* get_text(User* u, Key* k) {
    return get_item_hashmap(&(u->data), k);
}

bool delete_text(User* u, Key* k) {
    KeyValue* kv = get_item_hashmap(&(u->data), k);
    if (kv == NULL) {
        return false;
    } else {
        Operation o;
        o.opcode = OP_remove;
        o.kv = clone_keyvalue(kv);
        delete_item_hashmap(&(u->data), k);
        reset_redo_stack(u);
        push_stack(&(u->undo_stack), o);
        return true;
    }
}

bool apply_operation(User* u, Operation* o) {
    if (o->opcode == OP_add) {
        insert_element_hashmap(&(u->data), clone_keyvalue(&(o->kv)));
        return true;
    } else if (o->opcode == OP_remove) {
        return delete_item_hashmap(&(u->data), &(o->kv.key));
    }
    return false;
}

bool undo_action(User* u) {
    StackResult r = pop_stack(&(u->undo_stack));
    if (r.err == true) {
        return false;
    } else {
        r.ok.opcode = reverse_opcode(r.ok.opcode);
        apply_operation(u, &(r.ok));
        r.ok.opcode = reverse_opcode(r.ok.opcode);
        push_stack(&(u->redo_stack), r.ok);
        return true;
    }
}

bool redo_action(User* u) {
    StackResult r = pop_stack(&(u->redo_stack));
    if (r.err == true) {
        return false;
    } else {
        apply_operation(u, &(r.ok));
        push_stack(&(u->undo_stack), r.ok);
        return true;
    }
}

