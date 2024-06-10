#pragma once
#include "object.h"

// Virtual Functions
typedef char* (*ToString) (Object* object);

typedef struct Object {
    char* name;
    ToString toString;
} Object;
