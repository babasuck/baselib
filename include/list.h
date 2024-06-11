#pragma once

#include "object.h"
#include <stdlib.h>

typedef struct List List;

List* List_alloc();

void List_ctor(List* list);
void List_dtor(List* list);

int List_add(List* list, Object* el);
void List_print(List* list);

size_t List_getSize(List* list);
Object* List_at(List* list, size_t at);