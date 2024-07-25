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

Stack* Stack_create() {
    Stack* stack = Stack_alloc();
    Stack_ctor(stack);
    return stack;
}

int Stack_push(Stack* stack, Object* el) {
    if (el == NULL)
        return -1;
    LinkedList_insertStart(stack->list, el);
    return 0;
}

Object* Stack_pop(Stack* stack) {
    return LinkedList_removeStart(stack->list);
}

void Stack_print(Stack* stack) {
    printf("Stack : size - %d\n", LinkedList_getSize(stack->list));
    for(size_t i = 0; i < LinkedList_getSize(stack->list); i++) {
        printf("Element - %s \n", Object_toString(LinkedList_at(stack->list, i)));
    }
}