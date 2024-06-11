#pragma once


typedef struct Object Object;

void Object_ctr(Object* obj, const char* name);
void Object_dtor(Object* obj);
char* Object_ToString(Object* object);
int Object_HashCode(Object* object);