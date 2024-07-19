#pragma once

#include "object.h"

typedef struct LinkedList LinkedList;

LinkedList* LinkedList_alloc();
void LinkedList_ctor(LinkedList* list);
void LinkedList_dtor(LinkedList* list);
LinkedList* LinkedList_create();
int LinkedList_insertEnd(LinkedList* list, Object* el);
int LinkedList_insertStart(LinkedList* list, Object* el);
void LinkedList_print(LinkedList* list);