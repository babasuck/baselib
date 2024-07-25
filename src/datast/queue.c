#include "baselib.h"

#include <stdlib.h>
#include <stdio.h>

struct Queue {
    Object* object;
    LinkedList* list;
};

Queue* Queue_alloc() {
    return (Queue*)malloc(sizeof(Queue));
}

void Queue_ctor(Queue* q) {
    Object_ctor((Object*)q, "Queue");
    q->list = LinkedList_create();
}

void Queue_dtor(Queue* q) {
    Object_dtor((Object*)q);
    LinkedList_dtor(q->list);
}

Queue* Queue_create() {
    Queue* q = Queue_alloc();
    Queue_ctor(q);
    return q;
}

int Queue_Enqueue(Queue* q, Object* object) {
    return LinkedList_insertEnd(q->list, object);
}

Object* Queue_Dequeue(Queue* q) {
    return LinkedList_removeStart(q->list);
}
