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

void Object_ctr(Object* obj, const char* name) {
    obj->name = (char*)malloc(strlen(name) * sizeof(*obj->name));
    strncpy(obj->name, name, sizeof(name));
    // Setting V-Table
    obj->toString = __default_ToString;
    obj->hashCode = __default_HashCode;
}

void Object_dtor(Object* obj) {
    free(obj->name);
    free(obj);
}

char* Object_ToString(Object* object) {
    return object->toString(object);
}

int Object_HashCode(Object* object) {
    return object->hashCode(object);
}
