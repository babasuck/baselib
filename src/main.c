#include "baselib.h"

#include <stdio.h>

#define ARRSIZE 10

int main(int argc, char** argv) {
    Integer* int1 = Integer_create(1);
    Integer* int2 = Integer_create(2);
    Integer* int3 = Integer_create(3);
    Integer* int4 = Integer_create(1);
    //printf("int 1 and int 2 - %d\n", Object_EqualsTo(int1, int2));

    HashMap* hm = HashMap_create();
    HashMap_add(hm, "Avocado", (Object*)int1);
    HashMap_add(hm, "Apple", (Object*)int2);
    HashMap_add(hm, "Orange", (Object*)int3);
    HashMap_add(hm, "Banana", (Object*)int3);

    HashMap_print(hm);

    //printf("El - %s\n", Object_toString(HashMap_get(hm, "Apple")));

    HashMap_dtor(hm);
    Stack* stack = Stack_create();
    
    Stack_push(stack, (Object*)int1);
    Stack_push(stack, (Object*)int2);
    Stack_push(stack, (Object*)int3);

    Stack_pop(stack);
    Stack_pop(stack);

    Stack_push(stack, (Object*)int3);

    Stack_print(stack);

    Integer_dtor(int1);
    Integer_dtor(int2);
    Integer_dtor(int3);
    Integer_dtor(int4);
}