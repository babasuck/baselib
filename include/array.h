#pragma once

#include "object.h"
#include <stdlib.h>

typedef struct Array Array;

Array* Array_create(); /* alloc + ctor */
Array* Array_alloc();
void Array_ctor(Array* list);
void Array_dtor(Array* list);

int Array_add(Array* list, Object* el);
void Array_print(Array* list);

size_t Array_getSize(Array* list);
Object* Array_at(Array* list, size_t at);