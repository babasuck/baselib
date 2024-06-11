#include "baselib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Integer {
    Object object;
    int data;
} Integer;

// Overrided Virtual functions

char* __Integer_toString(Object* object) {
    Integer* integer = (Integer*)object;
    char* buf = (char*)malloc(255);
    itoa(integer->data, buf, 10);
    return buf;
}

int __Integer_hashCode(Object* object) {
    Integer* integer = (Integer*)object;
    return integer->data;
}

Object* __Integer_clone(Object* object) {
    Integer* integer = (Integer*)object;
    Integer* clone = Integer_alloc();
    Integer_ctor(clone, integer->data);
    return (Object*)clone;
}


Integer* Integer_alloc() {
    return (Integer*)malloc(sizeof(Integer)); 
}

void Integer_ctor(Integer* integer, int data) {
    Object_ctor((Object*)integer, "Integer");
    integer->data = data;

    // Setting V-Table
    integer->object.hashCode = __Integer_hashCode;
    integer->object.toString = __Integer_toString;
    integer->object.clone = __Integer_clone;
}

void Integer_dtor(Integer* integer) {
    Object_dtor((Object*)integer);
    free(integer);
}


