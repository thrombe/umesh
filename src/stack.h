
#ifndef STACK_HEADER
#define STACK_HEADER

#include "operation.h"
#include "helpers.h"


typedef struct {
    Operation* items;
    int len;
    int capacity;
} Stack; // Copy

typedef struct {
    Operation ok;
    bool err;
} StackResult; // Copy


Stack new_stack();
void print_stack(Stack* s);
void push_stack(Stack* a, Operation item);
StackResult pop_stack(Stack* s);


#endif // STACK_HEADER
