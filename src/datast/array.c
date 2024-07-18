#include "baselib.h"

#include "object_p.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 100

struct Array {
    Object object;
    size_t size;
    size_t capacity;
    Object** data;
};

// Overrided Virtual Functions

char* __array_ToString(Object* object) {
    Array* list = (Array*)object;
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
    sprintf(fstr, "Array of size - %zu, capacity - %zu, hashCode - %zu", list->size, list->capacity, Object_hashCode((Object*)list));
    strcat(buf, fstr);
    return buf;
}

size_t __array_HashCode(Object* object) {
    Array* list = (Array*)object;
    size_t hashCode = (list->capacity >> list->size) + 100;
    return hashCode;
}

Object* __array_Clone(Object* obj) {
    Array* list = (Array*)obj;
    Array* newList = Array_create();
    newList->size = list->size;
    newList->capacity = list->capacity;
    memcpy(newList->data, list->data, list->size * sizeof(Object*));
    return (Object*)newList;
}

Array* Array_alloc() {
    return (Array*)malloc(sizeof(Array));
}

void Array_ctor(Array* list) {
    Object_ctor((Object*)list, "Array");
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data = (Object**)malloc(list->capacity * sizeof(Object*));

    // Setting V-Table
    list->object.toString = __array_ToString;
    list->object.hashCode = __array_HashCode;
    list->object.clone = __array_Clone;
}

void Array_dtor(Array* list) {
    Object_dtor((Object*)list);
    free(list->data);
    free(list);
}

Array* Array_create() {
    Array* list = Array_alloc();
    Array_ctor(list);
    return list;
}

int Array_add(Array* list, Object* el) {
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


void Array_print(Array* list) {
    printf("[ ");
    for(int i = 0; i < list->size; i++) {
        char* buffer = Object_toString((Object*)list->data[i]);
        printf("%s ", buffer);
        free(buffer);
    }
    printf("]");
}

size_t Array_getSize(Array* list) {
    return list->size;
}

Object* Array_at(Array* list, size_t at) {
    return list->data[at];
}



