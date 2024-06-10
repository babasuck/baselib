#pragma once
#include "object.h"

// Virtual Functions
typedef char* (*ToString) (Object* object);
typedef int (*HashCode) (Object* object);

typedef struct Object {
    // V-Table
    ToString toString;
    HashCode hashCode;
    char* name;
} Object;

