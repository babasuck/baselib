#pragma once

#include <stdbool.h>

typedef struct HashSet HashSet;

HashSet* HashSet_alloc();
void HashSet_ctor(HashSet* hashSet);
void HashSet_dtor(HashSet* hashSet);


int HashSet_add(HashSet* hashSet, Object* el);
bool HashSet_contains(HashSet* hashSet, Object* object);
void HashSet_print(HashSet* hashSet);