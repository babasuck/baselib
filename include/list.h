#pragma once

#include "object.h"

typedef struct List List;

List* List_alloc();

void List_ctr(List* list);
void List_dtor(List* list);

int List_add(List* list, Object* el);
void List_print(List* list);