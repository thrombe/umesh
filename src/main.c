
#include<stdio.h>
#include<stdlib.h>

#include "user.h"
#include "ums.h"
#include "helpers.h"

int main() {
    UserManagementSystem ums = new_ums();

    insert_new_user(&ums, new_key_copied("user1"));
    insert_new_user(&ums, new_key_copied("erasd4"));
    insert_new_user(&ums, new_key_copied("esdarasdfdgs1"));
    insert_new_user(&ums, new_key_copied("usetwr"));
    insert_new_user(&ums, new_key_copied("werwwer"));
    print_ums(&ums);

    Key k = new_key_copied("erasd4");
    User* u = get_user(&ums, &k);
    insert_keyvalue_copied(u, "this", "is value");
    insert_keyvalue_copied(u, "this wdawdwa", "is valasdue");
    insert_keyvalue_copied(u, "asdasffwe", "is asdasdasrerfrfe");

    print_user(u);

    printf("\n");
    k = new_key_copied("this");
    KeyValue* kv = get_text(u, &k);
    print_str(kv->value, kv->value_width);
    printf("\n");

    delete_text(u, &k);
    print_user(u);

    printf("\n\ntesting undo: \n");
    undo_action(u);
    undo_action(u);
    print_user(u);
    printf("\ntesting redo: \n");
    redo_action(u);
    print_user(u);


    return 0;
}

