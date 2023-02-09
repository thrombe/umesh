

#include "operation.h"
#include "helpers.h"
#include<stdio.h>


void print_operation(Operation* op) {
    if (op->opcode == OP_add) {
        printf("added: { ");
    } else if (op->opcode == OP_remove) {
        printf("removed: { ");
    }
    printf("\"");
    print_key(&(op->kv.key));
    printf("\": \"");
    print_str((char*)(op->kv.value), op->kv.value_width);
    printf("\"");
    
    printf(" }");
}

OP_type reverse_opcode(OP_type op) {
    if (op == OP_remove) {
        return OP_add;
    } else if (op == OP_add) {
        return OP_remove;
    }

    printf("\nincorrect opcode\n");
    return 0;
}


