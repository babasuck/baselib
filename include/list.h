#pragma once

#include "object.h"

typedef struct LinkedList LinkedList, List;

LinkedList* LinkedList_alloc();
void LinkedList_ctor(LinkedList* list);
void LinkedList_dtor(LinkedList* list);
LinkedList* LinkedList_create();

int LinkedList_insertEnd(LinkedList* list, Object* el);
int LinkedList_insertStart(LinkedList* list, Object* el);
Object* LinkedList_removeStart(LinkedList* list);

Object* LinkedList_at(LinkedList* list, size_t at);

size_t LinkedList_getSize(LinkedList* list);

void LinkedList_print(LinkedList* list);