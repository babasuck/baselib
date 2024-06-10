#pragma once

typedef struct List List;

List* List_alloc();

void List_ctr(List* list);
void List_dtor(List* list);

void List_add(List* list, void* el);
void List_print(List* list);