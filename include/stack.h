#pragma once

typedef struct Stack Stack;

Stack* Stack_alloc();
void Stack_ctor(Stack* stack);
void Stack_dtor(Stack* stack);
Stack* Stack_create();

int Stack_push(Stack* stack, Object* el);
Object* Stack_pop(Stack* stack);

void Stack_print(Stack* stack);
 