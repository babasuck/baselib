#include "object.h"
#include "object_p.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Virtual Functions

char* __default_ToString(Object* object) {
    size_t len = strlen(object->name) + 124;
    char* buf = (char*)malloc(len * sizeof(*buf));
    memset(buf, 0, len * sizeof(*buf));
    snprintf(buf, len * sizeof(*buf), "Object - %s at %p hashCode - %d", object->name, object, object->hashCode(object));
    return buf;
}

int __default_HashCode(Object* object) {
    int hashCode = 0;
    for(int i = 0; i < sizeof(object->name); i++) {
        hashCode += object->name[i];
    }
    return hashCode;
}

Object* __default_clone(Object* object) {
    //Not implemented
}

void Object_ctr(Object* obj, char* name) {
    obj->name = (char*)malloc((strlen(name) + 1) * sizeof(*obj->name));
    strcpy(obj->name, name);
    // Setting V-Table
    obj->toString = __default_ToString;
    obj->hashCode = __default_HashCode;
    obj->clone = __default_clone;
}

void Object_dtor(Object* obj) {
    free(obj->name);
}

char* Object_toString(Object* object) {
    return object->toString(object);
}

int Object_hashCode(Object* object) {
    return object->hashCode(object);
}

Object* Object_clone(Object* object) {
    return object->clone(object);
}