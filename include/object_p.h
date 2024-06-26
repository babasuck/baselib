#pragma once
#include "object.h"

// Virtual Functions
typedef char* (*ToString) (Object* object);
typedef size_t (*HashCode) (Object* object);
typedef Object* (*Clone) (Object*);

typedef struct Object {
    // V-Table
    ToString toString;
    HashCode hashCode;
    Clone clone;
    char* name;
} Object;

