#pragma once
#include "object.h"

// Virtual Functions
typedef char* (*ToString) (Object* object);
typedef size_t (*HashCode) (Object* object);
typedef Object* (*Clone) (Object*);
typedef bool(*EqualsTo) (Object*, Object*);

struct Object {
    // V-Table
    ToString toString;
    HashCode hashCode;
    Clone clone;
    EqualsTo equalsTo;
    const char* name;
};

char* Object_toString(Object* object);

