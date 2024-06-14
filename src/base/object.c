#include "baselib.h"

#include "object.h"
#include "object_p.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

// Virtual Functions

char* __default_ToString(Object* object) {
    size_t len = strlen(object->name) + 124;
    char* buf = (char*)malloc(len * sizeof(*buf));
    memset(buf, 0, len * sizeof(*buf));
    snprintf(buf, len * sizeof(*buf), "Object - %s at %p hashCode - %d", object->name, object, object->hashCode(object));
    return buf;
}

size_t __default_HashCode(Object* object) {
    size_t hashCode = 0;
    for(size_t i = 0; i < sizeof(object->name); i++) {
        hashCode += object->name[i];
    }
    return hashCode;
}


void Object_ctor(Object* obj, char* name) {
    obj->name = (char*)malloc((strlen(name) + 1) * sizeof(*obj->name));
    strcpy(obj->name, name);
    // Setting V-Table
    obj->toString = __default_ToString;
    obj->hashCode = __default_HashCode;
    obj->clone = 0;
}

void Object_dtor(Object* obj) {
    free(obj->name);
}

char* Object_toString(Object* object) {
    return object->toString(object);
}

size_t Object_hashCode(Object* object) {
    return object->hashCode(object);
}

Object* Object_clone(Object* object) {
    assert(object->clone);
    return object->clone(object);
}