#pragma once


typedef struct Object Object;

void Object_ctr(Object* obj, char* name);
void Object_dtor(Object* obj);
char* Object_toString(Object* object);
int Object_hashCode(Object* object);
Object* Object_clone(Object* object);