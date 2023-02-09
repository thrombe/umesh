
#ifndef USER_HEADER
#define USER_HEADER

#include "operation.h"
#include "stack.h"
#include "keyvalue.h"
#include "hashmap.h"
#include "helpers.h"


typedef struct {
    Stack undo_stack; // pop from this and apply reverse to undo
    Stack redo_stack; // pop from this and apply to redo
    HashMap data;
} User; // !Copy


User* new_user();
void print_user(User* u);
void reset_redo_stack(User* u);
void insert_keyvalue(User* u, KeyValue kv);
void insert_keyvalue_copied(User* u, char* key, char* value);
KeyValue* get_text(User* u, Key* k);
bool delete_text(User* u, Key* k);
bool apply_operation(User* u, Operation* o);
bool undo_action(User* u);
bool redo_action(User* u);


#endif // USER_HEADER
