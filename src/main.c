
#include<stdio.h>
#include<stdlib.h>

#include "keyvalue.h"
#include "user.h"
#include "ums.h"
#include "helpers.h"

int test_cases() {
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

    free_key(&k);
    
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

    free_ums(&ums);
    return 0;
}

int menu_driven_program() {
    printf("enter the following code for the corresponding actions:\n");
    printf("    0 => exit\n");
    printf("    1 => print ums\n");
    printf("    2 => print user\n");
    printf("    3 => create user\n");
    printf("    4 => add text to user\n");
    printf("    5 => get text from user\n");
    printf("    6 => delete text from user\n");
    printf("    7 => delete user\n");
    printf("    8 => undo user action\n");
    printf("    9 => redo user action\n");
    printf("    _ => invalid opcode\n");

    UserManagementSystem ums = new_ums();

    while (1) {
        int opcode = 0;
        printf("\nenter opcode: ");
        scanf("%d", &opcode);

        int buf_size = 1000;
        char* user_name = (char*)malloc(sizeof(char)*buf_size);
        char* key_name = (char*)malloc(sizeof(char)*buf_size);
        char* text = (char*)malloc(sizeof(char)*buf_size);
        Key k = new_key(NULL, 0);
        Key k2 = new_key(NULL, 0);
        User* u = NULL;
        KeyValue* text_kv = NULL;

        int break_loop = 0;
        switch (opcode) {
            case 0:
                break_loop = 1;
                break;
            case 1:
                print_ums(&ums);
                break;
            case 2:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                u = get_user(&ums, &k);
                if (u == NULL) {
                    printf("user with the given username does not exist :/\n");
                } else {
                    print_user(u);
                }
                free_key(&k);
                break;
            case 3:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                insert_new_user(&ums, k);
                k = new_key(NULL, 0); // key moved
                break;
            case 4:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                u = get_user(&ums, &k);
                if (u == NULL) {
                    printf("user with the given username does not exist :/\n");
                } else {
                    printf("enter key for the text: ");
                    scanf("%s", key_name);
                    printf("enter text: ");
                    scanf("%s", text);
                    insert_keyvalue_copied(u, key_name, text);
                }
                free_key(&k);
                break;
            case 5:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                u = get_user(&ums, &k);
                if (u == NULL) {
                    printf("user with the given username does not exist :/\n");
                } else {
                    printf("enter key for the text: ");
                    scanf("%s", key_name);
                    k2 = new_key_copied(key_name);
                    text_kv = get_text(u, &k2);
                    printf("the text is: \"");
                    print_str(text_kv->value, text_kv->value_width);
                    printf("\"\n");
                    text_kv = NULL;
                    free_key(&k2);
                }
                free_key(&k);
                break;
            case 6:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                u = get_user(&ums, &k);
                if (u == NULL) {
                    printf("user with the given username does not exist :/\n");
                } else {
                    printf("enter key for the text: ");
                    scanf("%s", key_name);
                    k2 = new_key_copied(key_name);
                    delete_text(u, &k2);
                    free_key(&k2);
                }
                free_key(&k);
                break;
            case 7:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                delete_user(&ums, &k);
                free_key(&k);
                break;
            case 8:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                u = get_user(&ums, &k);
                if (u == NULL) {
                    printf("user with the given username does not exist :/\n");
                } else {
                    undo_action(u);
                }
                free_key(&k);
                break;
            case 9:
                printf("enter username: ");
                scanf("%s", user_name);
                k = new_key_copied(user_name);
                u = get_user(&ums, &k);
                if (u == NULL) {
                    printf("user with the given username does not exist :/\n");
                } else {
                    redo_action(u);
                }
                free_key(&k);
                break;
            default:
                printf("invalid opcode\n");
                break;
        }
        if (break_loop != 0) {
            printf("exitting\n\n");
            break;
        }
    }

    free_ums(&ums);
    return 0;
}

int main() {
    // test_cases();
    menu_driven_program();
    return 0;
}
