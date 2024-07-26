#pragma once

typedef struct HashMap HashMap, Map, Dict;

HashMap* HashMap_alloc();
void HashMap_ctor(HashMap* hm);
void HashMap_dtor(HashMap* hm);
HashMap* HashMap_create();


int HashMap_add(HashMap* hashMap, const char* key, Object* value);
Object* HashMap_get(HashMap* hashMap, const char* key);

void HashMap_print(HashMap* hashMap);
int64_t HashMap_contains(HashMap* hashMap, const char* key);