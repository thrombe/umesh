

#include "operation.h"
#include "helpers.h"
#include "stack.h"
#include<stdlib.h>
#include<stdio.h>


Stack new_stack() {
    Stack a;
    a.len = 0;
    a.capacity = 0;
    a.items = NULL;
    return a;
}

void print_stack(Stack* s) {
    printf("[\n");
    for (int i=0; i<s->len; i++) {
        printf("    ");
        print_operation(&(s->items[i]));
        printf("\n");
    }
    printf("]\n");
}

void push_stack(Stack* a, Operation item) {
    if (a->capacity == a->len) {
        a->capacity = (a->capacity*3)/2;
        if (a->capacity == 0) {
            a->capacity = 2;
        }
        a->items = (Operation* )(realloc(a->items, sizeof(Operation)*a->capacity));
    }
    a->items[a->len] = item;
    a->len += 1;
}

StackResult pop_stack(Stack* s) {
    StackResult r;
    r.err = false;
    if (s->len > 0) {
        r.ok = s->items[s->len-1];
        s->len -= 1;
    } else {
        r.err = true;
    }
    return r;
}
