#include "primitive.h"

#include "object_p.h"

#include <stdlib.h>
#include <stdio.h>

struct Primitive {
    Object object;
    enum { INTEGER, DOUBLE } type;
    union {
        int64_t intValue;
        long double doubleValue;
    } data;
};

static char* __Primitive_toString(Object* object) {
    Primitive* primitive = (Primitive*)object;
    char* buf = (char*)malloc(255);
    switch(primitive->type) {
        case INTEGER:
            sprintf(buf, "%d", primitive->data.intValue);
            break;
        case DOUBLE:
            sprintf(buf, "%d", primitive->data.doubleValue);
            break;
    }
    return buf;
}

static size_t __Primitive_hashCode(Object* object) {
    Primitive* primitive = (Primitive*)object;
    switch(primitive->type) {
        case INTEGER:
            return primitive->data.intValue;
        case DOUBLE:
            return primitive->data.doubleValue;
    }
}

static Object* __Primitive_clone(Object* object) {
    Primitive* primitive = (Primitive*)object;
    switch(primitive->type) {
        case INTEGER:
            return (Object*)Primitive_create(primitive->data.intValue);
        case DOUBLE:
            return (Object*)Primitive_create(primitive->data.doubleValue);
    }
}

static bool __Primitive_EqualsTo(Object* one, Object* two) {
    Primitive* primitive_one = (Primitive*)one;
    Primitive* primitive_two = (Primitive*)two;
    if (primitive_one->type != primitive_two->type)
        return false;
    switch(primitive_one->type) {
        case INTEGER:
            if(primitive_one->data.intValue != primitive_two->data.intValue)
                return false;
            break;
        case DOUBLE:
            if(primitive_one->data.doubleValue != primitive_two->data.doubleValue)
                return false;
            break;
    }
    return true;
}

Primitive* Primitive_Integer_create(int64_t data) {
    Primitive* primitive = (Primitive*)malloc(sizeof(Primitive));
    Object_ctor((Object*)primitive, "Integer Primitive");
    primitive->data.intValue = data;
    primitive->type = INTEGER;
    return primitive;
}

Primitive* Primitive_Double_create(long double data) {
    Primitive* primitive = (Primitive*)malloc(sizeof(Primitive));
    Object_ctor((Object*)primitive, "Double Primitive");
    primitive->data.doubleValue = data;
    primitive->type = DOUBLE;
    return primitive;
}

