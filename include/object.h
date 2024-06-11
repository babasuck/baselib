#pragma once


typedef struct Object Object;

void Object_ctor(Object* obj, char* name);
void Object_dtor(Object* obj);
char* Object_toString(Object* object);
int Object_hashCode(Object* object);
Object* Object_clone(Object* object);