#pragma once

#include <stdbool.h>

typedef struct Object Object;
typedef void (*FuncForAll)(Object* object);

void Object_ctor(Object* obj, char* name);
void Object_dtor(Object* obj);
size_t Object_hashCode(Object* object);
Object* Object_clone(Object* object);
bool Object_EqualsTo(Object* one, Object* two);

char* Object_toString(Object* object);