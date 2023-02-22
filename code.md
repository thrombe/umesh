
## All files
```
├── input.txt
├── output.txt
└── src
    ├── hashmap.c
    ├── hashmap.h
    ├── helpers.c
    ├── helpers.h
    ├── keyvalue.c
    ├── keyvalue.h
    ├── linked_list.c
    ├── linked_list.h
    ├── main.c
    ├── operation.c
    ├── operation.h
    ├── stack.c
    ├── stack.h
    ├── ums.c
    ├── ums.h
    ├── user.c
    └── user.h
```

## src/main.c
```C
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
```

## src/hashmap.h
```C
#ifndef HASHMAP_HEADER
#define HASHMAP_HEADER


#include "linked_list.h"
#include "keyvalue.h"
#include "helpers.h"


typedef struct {
    LinkedList* data;
    int size;
} HashMap; // Copy


HashMap new_hashmap();
int hash(void* data, int width);
int hash_key(Key* key);
int get_index(HashMap* m, Key* k);
bool key_match(Key* k1, Key* k2);
KeyValue* get_item_hashmap(HashMap* m, Key* k);
void insert_element_hashmap(HashMap* m, KeyValue kv);
bool delete_item_hashmap(HashMap* m, Key* k);
void print_hashmap(HashMap* m);
void free_hashmap(HashMap* m);


#endif // HASHMAP_HEADER
```

## src/hashmap.c
```C
#include "hashmap.h"
#include "linked_list.h"
#include "keyvalue.h"
#include "helpers.h"
#include<stdlib.h>
#include<stdio.h>


HashMap new_hashmap() {
    HashMap m;
    // m.size = 421;
    m.size = 41;
    m.data = malloc(sizeof(LinkedList)*m.size);
    for (int i=0; i<m.size; i++) {
        m.data[i] = new_llist();
    }
    return m;
}

// https://stackoverflow.com/a/7666577
int hash(void* data, int width) {
    char* str = (char*)data;
    int hash = 5381;

    for (int i=0; i<width; i++) {
        int c = (int)str[i];
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int hash_key(Key* key) {
    return hash(key->key, key->key_width);
}

int get_index(HashMap* m, Key* k) {
    int h = hash(k->key, k->key_width);
    h %= m->size;
    h += m->size; // -ve mod :/
    h %= m->size;
    return h;
}

bool key_match(Key* k1, Key* k2) {
    if (k1->key_width != k2->key_width) {
        return false;
    } else {
        for (int i=0; i<k1->key_width; i++) {
            if (k1->key[i] != k2->key[i]) {
                return false;
            }
        }
        
        return true;
    }
}

KeyValue* get_item_hashmap(HashMap* m, Key* k) {
    int i = get_index(m, k);
    LinkedList* ll = &(m->data[i]);
    Node* n = ll->first;
    while (n != NULL) {
        if (key_match(&(n->val.key), k)) {
            return &(n->val);
        }
        n = n->next;
    }
    return NULL;
}

void insert_element_hashmap(HashMap* m, KeyValue kv) {
    int h = get_index(m, &(kv.key));
    LinkedList* ll = &(m->data[h]);
    KeyValue* dest_kv = get_item_hashmap(m, &(kv.key));
    if (dest_kv == NULL) {
        insert_at_front_ll(ll, kv);
    } else {
        free_keyvalue(dest_kv);
        *dest_kv = kv;
    }
}

bool delete_item_hashmap(HashMap* m, Key* k) {
    int i = get_index(m, k);
    LinkedList* ll = &(m->data[i]);
    Node** p = &(ll->first);
    Node* n = ll->first;
    while (n != NULL) {
        if (key_match(&(n->val.key), k)) {
            *p = n->next;
            n->next = NULL;
            free_node(n);
            return true;
        }
        p = &(n->next);
        n = n->next;
    }
    return false;
}

void print_hashmap(HashMap* m) {
    printf("---\n");
    for (int i=0; i<m->size; i++) {
        printf(" |-> ");
        print_llist(&(m->data[i]));
    }
    printf("---\n");
}

void free_hashmap(HashMap* m) {
    if (m != NULL) {
        for (int i=0; i<m->size; i++) {
            free_llist(&(m->data[i]));
        }
        free(m->data);
        m->data = NULL;
        m->size = 0;
    }
}
```

## src/helpers.h
```C
#ifndef HELPERS_HEADER
#define HELPERS_HEADER


#define false 0
#define true 1
typedef int bool;

char* heap_str(char* str);
int str_len(char* str);
void print_str(char* str, int len);


#endif // HELPERS_HEADER
```

## src/helpers.c
```C
#include<stdlib.h>
#include<stdio.h>


// non null-terminated heap string
char* heap_str(char* str) {
    int len;
    for (len=0; str[len] != '\0'; len++) {}
    char* string = malloc(sizeof(char)*len);
    for (int i=0; i<len; i++) {
        string[i] = str[i];
    }
    return string;
}

// takes in null-terminated string
int str_len(char* str) {
    int len;
    for (len=0; str[len] != '\0'; len++) {}
    return len;
}

void print_str(char* str, int len) {
    for (int i=0; i<len; i++) {
        printf("%c", str[i]);
    }
}
```

## src/keyvalue.h
```C
#ifndef KEYVALUE_HEADER
#define KEYVALUE_HEADER


typedef struct {
    char* key;
    int key_width;
} Key; // Copy


typedef struct {
    Key key;

    void* value;
    int value_width;
} KeyValue; // Copy


Key new_key(char* key, int key_width);
Key new_key_copied(char* key);
void print_key(Key* k);
void free_key(Key* k);

void print_keyvalue(KeyValue* kv);
KeyValue new_keyvalue(char* key, int key_width, void* value, int value_width);
KeyValue clone_keyvalue(KeyValue* kv);
void free_keyvalue(KeyValue* kv);


#endif // KEYVALUE_HEADER
```

## src/keyvalue.c
```C
#include "keyvalue.h"
#include "helpers.h"
#include<stdlib.h>
#include<stdio.h>


// pointer takes ownership
Key new_key(char* key, int key_width) {
    Key k;
    k.key = key;
    k.key_width = key_width;
    return k;
}

// takes in null-terminated string
Key new_key_copied(char* key) {
    return new_key(heap_str(key), str_len(key));
}

void print_key(Key* k) {
    print_str(k->key, k->key_width);
}

void free_key(Key* k) {
    if (k != NULL) {
        free(k->key);
        k->key = NULL;
        k->key_width = 0;
    }
}



void print_keyvalue(KeyValue* kv) {
    if (kv == NULL) {
        return;
    }

    printf("\"");
    print_key(&(kv->key));
    printf("\": ");

    printf("\"");
    printf("%ld", kv->value);
    printf("\" ");
}

// takes ownership of both pointers
KeyValue new_keyvalue(char* key, int key_width, void* value, int value_width) {
    KeyValue kv;
    kv.key = new_key(key, key_width);

    kv.value = value;
    kv.value_width = value_width;
    return kv;
}

KeyValue clone_keyvalue(KeyValue* kv) {
    char* key = malloc(sizeof(char)*kv->key.key_width);
    for (int i=0; i<kv->key.key_width; i++) {
        key[i] = kv->key.key[i];
    }

    void* value = malloc(kv->value_width);
    char* source_val = (char*)(kv->value);
    char* temp_val = (char*)value; // for alignment maybe
    for (int i=0; i<kv->value_width; i++) {
        temp_val[i] = source_val[i];
    }
    
    KeyValue kv2;

    kv2.key.key = key;
    kv2.key.key_width = kv->key.key_width;

    kv2.value = value;
    kv2.value_width = kv->value_width;
    return kv2;
}

void free_keyvalue(KeyValue* kv) {
    if (kv != NULL) {
        free_key(&(kv->key));
        free(kv->value);
        kv->value = NULL;
        kv->value_width = 0;
    }
}
```

## src/linked_list.h
```C
#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER


#include "keyvalue.h"
#include "helpers.h"


typedef struct Node {
    struct Node* next;
    KeyValue val;
} Node; // !Copy


typedef struct {
    Node* first;
} LinkedList; // Copy


void free_node(Node* n);
void print_node(Node* n);
LinkedList new_llist();
bool insert_at_position_ll(LinkedList* a, int pos, KeyValue element);
void insert_at_front_ll(LinkedList* a, KeyValue kv);
void print_llist(LinkedList* a);
void free_llist(LinkedList* a);


#endif // LINKEDLIST_HEADER
```

## src/linked_list.c
```C
#include "keyvalue.h"
#include "linked_list.h"
#include "helpers.h"
#include<stdlib.h>
#include<stdio.h>

// recursive
void free_node(Node* n) {
    if (n != NULL) {
        free_keyvalue(&(n->val));
        free_node(n->next);
        n->next = NULL;
        free(n);
    }
}

void print_node(Node* n) {
    if (n == NULL) {
        return;
    }
    print_keyvalue(&(n->val));
}



LinkedList new_llist() {
    LinkedList a;
    a.first = NULL;
    return a;
}

bool insert_at_position_ll(LinkedList* a, int pos, KeyValue element) {
    if (pos < 1) {
        return false;
    }
    int index = pos - 1;

    Node* b = a->first;
    if (b == NULL) {
        if (index != 0) {
            return false;
        }
        a->first = malloc(sizeof(Node));
        a->first->val = element;
        a->first->next = NULL;
        return true;
    }

    if (index == 0) {
        b = malloc(sizeof(Node));
        b->val = element;
        b->next = a->first;
        a->first = b;
        return true;
    }

    for (int i=1; i<index; i++) {
        if (b->next == NULL) {
            return false;
        }
        b = b->next;
    }

    Node* c = malloc(sizeof(Node));
    c->next = b->next;
    c->val = element;
    b->next = c;
    return true;
}

void insert_at_front_ll(LinkedList* a, KeyValue kv) {
    insert_at_position_ll(a, 1, kv);
}

void print_llist(LinkedList* a) {
    printf("[ ");
    Node* b = a->first;
    while (b != NULL) {
        printf("-> ");
        print_node(b);
        b = b->next;
    }
    printf("]\n");
}

void free_llist(LinkedList* a) {
    if (a != NULL) {
        free_node(a->first);
        a->first = NULL;
    }
}

```

## src/operation.h
```C
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
```

## src/operation.c
```C
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

```

## src/stack.h
```C
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
```

## src/stack.c
```C
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
```

## src/ums.h
```C
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
void free_ums(UserManagementSystem* ums);


#endif // UMS_HEADER
```

## src/ums.c
```C
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
```

## src/user.h
```C
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
```

## src/user.c
```C
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
```

