
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
void print_keyvalue(KeyValue* kv);
KeyValue new_keyvalue(char* key, int key_width, void* value, int value_width);
KeyValue clone_keyvalue(KeyValue* kv);
void free_keyvalue(KeyValue* kv);


#endif // KEYVALUE_HEADER