#include "baselib.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Integer {
    Object object;
    int data;
} Integer;

// Virtual functions

char* __Integer_ToString(Object* object) {
    Integer* integer = (Integer*)object;
    char* buf = (char*)malloc(255);
    itoa(integer->data, buf, 10);
    return buf;
}

int __Integer_HashCode(Object* object) {
    Integer* integer = (Integer*)object;
    return integer->data;
}

Integer* Integer_alloc() {
    return (Integer*)malloc(sizeof(Integer)); 
}

void Integer_ctor(Integer* integer, int data) {
    Object_ctr((Object*)integer, "Integer");
    integer->data = data;
    integer->object.hashCode = __Integer_HashCode;
    integer->object.toString = __Integer_ToString;
}

void Integer_dtor(Integer* integer) {
    Object_dtor((Object*)integer);
}


