#include "baselib.h"

#include "object_p.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Integer {
    Object object;
    uint64_t data;
};

// Overrided Virtual functions

static char* __Integer_toString(Object* object) {
    Integer* integer = (Integer*)object;
    char* buf = (char*)malloc(255);
    _ltoa(integer->data, buf, 10);
    return buf;
}

static size_t __Integer_hashCode(Object* object) {
    Integer* integer = (Integer*)object;
    return integer->data;
}

static Object* __Integer_clone(Object* object) {
    Integer* integer = (Integer*)object;
    Integer* clone = Integer_alloc();
    Integer_ctor(clone, integer->data);
    return (Object*)clone;
}

static bool __Integer_EqualsTo(Object* one, Object* two) {
    if (strcmp(one->name, two->name) || (((Integer*)one)->data != ((Integer*)two)->data))
        return false;
    return true;
    
}

Integer* Integer_alloc() {
    return (Integer*)malloc(sizeof(Integer)); 
}

void Integer_ctor(Integer* integer, uint64_t data) {
    Object_ctor((Object*)integer, "Integer");
    integer->data = data;

    // Setting V-Table
    integer->object.hashCode = __Integer_hashCode;
    integer->object.toString = __Integer_toString;
    integer->object.clone = __Integer_clone;
    integer->object.equalsTo = __Integer_EqualsTo;
}

void Integer_dtor(Integer* integer) {
    Object_dtor((Object*)integer);
    free(integer);
}

Integer* Integer_create(uint64_t data) {
    Integer* integer = Integer_alloc();
    Integer_ctor(integer, data);
    return integer;
}

uint64_t Integer_getInt(Integer* integer) {
    return integer->data;
}
