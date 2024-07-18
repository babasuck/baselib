#pragma once

typedef struct Object Object;

void Object_ctor(Object* obj, char* name);
void Object_dtor(Object* obj);
size_t Object_hashCode(Object* object);
Object* Object_clone(Object* object);