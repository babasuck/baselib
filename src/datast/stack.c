#include "baselib.h"
#include "object_p.h"

struct Stack {
    Object obj;
    LinkedList* list;
};


Stack* Stack_alloc() {
    return (Stack*)malloc(sizeof(Stack));
}

void Stack_ctor(Stack* stack) {
    Object_ctor((Object*)stack, "Stack");
    stack->list = LinkedList_create();
}

void Stack_dtor(Stack* stack) {
    Object_dtor((Object*)stack);
    LinkedList_dtor(stack->list);
}

int Stack_push(Stack* stack, Object* el) {
    if (el == NULL)
        return -1;
    LinkedList_insertStart(stack->list, el);
}

int Stack_pop(Stack* stack, Object* el) {
    if (el == NULL)
        return -1;
    //delete
}