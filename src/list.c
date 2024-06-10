#include "baselib.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 100

typedef struct List {
    Object object;
    void** data;
    uint64_t size;
    uint64_t capacity;
} List;


// Overrided Virtual Functions

char* __list_ToString(Object* object) {
    List* list = (List*)object;
    size_t bufsize = 256;
    char* buf = (char*)malloc(bufsize * sizeof(*buf));
    memset(buf, 0, bufsize * sizeof(*buf));
    snprintf(buf, bufsize, "List of size - %d, capacity - %d, hashCode - %d", list->size, list->capacity, Object_HashCode((Object*)list));
    return buf;
}

int __list_HashCode(Object* object) {
    List* list = (List*)object;
    int hashCode = (list->capacity >> list->size) + 100;
    return hashCode;
}



List* List_alloc() {
    return (List*)malloc(sizeof(List));
}

void List_ctr(List* list) {
    Object_ctr(&list->object, "List");
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data = calloc(list->capacity, sizeof(void*));

    // Setting V-Table
    list->object.toString = __list_ToString;
    list->object.hashCode = __list_HashCode;
}

void List_dtor(List* list) {
    free(list->data);
    free(list);
}

void List_add(List* list, void* el) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(void*));
    }
    list->data[list->size++] = el;
}

void List_print(List* list) {
    for(int i = 0; i < list->size; i++) {
        char* buffer = Object_ToString((Object*)list->data[i]);
        printf("%s\n", buffer);
        free(buffer);
    }
}



