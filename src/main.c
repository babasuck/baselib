#include "baselib.h"

#include <stdio.h>

#define ARRSIZE 10

int main(int argc, char** argv) {
    Integer* int1 = Integer_create(1);
    Integer* int2 = Integer_create(2);
    Integer* int3 = Integer_create(3);

    LinkedList* list = LinkedList_create();
    LinkedList_print(list);
    LinkedList_insertEnd(list, (Object*)int1);
    LinkedList_insertEnd(list, (Object*)int2);
    LinkedList_insertEnd(list, (Object*)int3);
    LinkedList_print(list);
    printf("\n---------------------------------------\n");
    LinkedList_insertStart(list, (Object*)int3);
    LinkedList_print(list);
    LinkedList_dtor(list);
    Integer_dtor(int1);
    Integer_dtor(int2);
    Integer_dtor(int3);
}