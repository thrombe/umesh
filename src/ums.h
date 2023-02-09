
#ifndef UMS_HEADER
#define UMS_HEADER

#include "keyvalue.h"
#include "helpers.h"
#include "user.h"

typedef struct {
    // Queue op_queue;
    HashMap users;
} UserManagementSystem; // Copy


UserManagementSystem new_ums();
void insert_new_user(UserManagementSystem* ums, Key k);
void print_ums(UserManagementSystem* ums);
User* get_user(UserManagementSystem* ums, Key* k);
bool delete_user(UserManagementSystem* ums, Key* k);


#endif // UMS_HEADER
