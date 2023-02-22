

#include "keyvalue.h"
#include "helpers.h"
#include "ums.h"
#include "hashmap.h"
#include "user.h"
#include<stdlib.h>


UserManagementSystem new_ums() {
    UserManagementSystem ums;
    ums.users = new_hashmap();
    return ums;
}

// deletes old user if key is already present
void insert_new_user(UserManagementSystem* ums, Key k) {
    insert_element_hashmap(&(ums->users), new_keyvalue(k.key, k.key_width, (void*)new_user(), sizeof(User)));
}

void print_ums(UserManagementSystem* ums) {
    print_hashmap(&(ums->users));
}

User* get_user(UserManagementSystem* ums, Key* k) {
    KeyValue* kv = get_item_hashmap(&(ums->users), k);
    if (kv == NULL) {
        return NULL;
    } else {
        return (User*)(kv->value);
    }
}

bool delete_user(UserManagementSystem* ums, Key* k) {
    return delete_item_hashmap(&(ums->users), k);
}

void free_ums(UserManagementSystem* ums) {
    if (ums != NULL) {
        free_hashmap(&(ums->users));
    }
}

