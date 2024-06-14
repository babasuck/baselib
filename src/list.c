#include "baselib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 100

typedef struct List {
    Object object;
    size_t size;
    size_t capacity;
    Object** data;
} List;


// Overrided Virtual Functions

char* __list_ToString(Object* object) {
    List* list = (List*)object;
    size_t bufsize = list->size * 64 + 256;
    char* buf = (char*)malloc(bufsize * sizeof(*buf));
    memset(buf, 0, bufsize * sizeof(*buf));
    strcat(buf, "[ ");
    for(int i = 0; i < list->size; i++) {
        char* buffer = Object_toString((Object*)list->data[i]);
        strcat(buffer, " ");
        strcat(buf, buffer);
        free(buffer);
    }
    strcat(buf, "] ");
    char fstr[255] = {0};
    sprintf(fstr, "List of size - %zu, capacity - %zu, hashCode - %zu", list->size, list->capacity, Object_hashCode((Object*)list));
    strcat(buf, fstr);
    return buf;
}

size_t __list_HashCode(Object* object) {
    List* list = (List*)object;
    size_t hashCode = (list->capacity >> list->size) + 100;
    return hashCode;
}

Object* __list_clone(Object* obj) {
    List* list = (List*)obj;
    List* newList = List_create();
    newList->size = list->size;
    newList->capacity = list->capacity;
    memcpy(newList->data, list->data, list->size * sizeof(Object*));
    return (Object*)newList;
}

List* List_alloc() {
    return (List*)malloc(sizeof(List));
}

void List_ctor(List* list) {
    Object_ctor((Object*)list, "List");
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data = (Object**)malloc(list->capacity * sizeof(Object*));

    // Setting V-Table
    list->object.toString = __list_ToString;
    list->object.hashCode = __list_HashCode;
    list->object.clone = __list_clone;
}

void List_dtor(List* list) {
    Object_dtor((Object*)list);
    free(list->data);
    free(list);
}

List* List_create() {
    List* list = List_alloc();
    List_ctor(list);
    return list;
}

int List_add(List* list, Object* el) {
    if(el == NULL)
        return -1;
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        Object** newData = (Object**)realloc(list->data, list->capacity * sizeof(Object*));
        for (size_t i = 0; i < list->size; i++) {
            newData[i] = list->data[i];
        }
        newData[list->size++] = el;
        list->data = newData;
        return 0;
    }
    list->data[list->size++] = el;
    return 0;
}


void List_print(List* list) {
    printf("[ ");
    for(int i = 0; i < list->size; i++) {
        char* buffer = Object_toString((Object*)list->data[i]);
        printf("%s ", buffer);
        free(buffer);
    }
    printf("]");
}

size_t List_getSize(List* list) {
    return list->size;
}

Object* List_at(List* list, size_t at) {
    return list->data[at];
}



