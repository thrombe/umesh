
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
