#pragma once

#include "object.h"

typedef struct Queue Queue;

Queue* Queue_alloc();
void Queue_ctor(Queue* q);
void Queue_dtor(Queue* q);
Queue* Queue_create();

int Queue_Enqueue(Queue* q, Object* object);
Object* Queue_Dequeue(Queue* q);
