
#ifndef OPERATION_HEADER
#define OPERATION_HEADER

#include "keyvalue.h"


#define OP_add 1
#define OP_remove 2
typedef int OP_type;

typedef struct {
    OP_type opcode;
    KeyValue kv;
} Operation; // Copy


void print_operation(Operation* op);
OP_type reverse_opcode(OP_type op);


#endif // OPERATION_HEADER
