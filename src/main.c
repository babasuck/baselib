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
    HashMap_add(hm, "Avocado", int1);
    HashMap_add(hm, "Apple", int2);
    HashMap_add(hm, "Orange", int3);
    HashMap_add(hm, "Banana", int3);

    HashMap_print(hm);

    HashMap_dtor(hm);
    // HashSet* hs = HashSet_create();
    // HashSet_add(hs, (Object*)int1);
    // HashSet_add(hs, (Object*)int2);
    // HashSet_add(hs, (Object*)int3);
    // HashSet_add(hs, (Object*)int4);
    // HashSet_print(hs);
    // printf("contains - %d\n", HashSet_contains(hs, (Object*)int3));

    // Array* arr1 = Array_create();
    // Array* arr2 = Array_create();

    // Array_add(arr1, (Object*)int1);
    // Array_add(arr1, (Object*)int2);
    // Array_add(arr1, (Object*)int3);

    
    // Array_add(arr2, (Object*)int1);
    // Array_add(arr2, (Object*)int2);
    // Array_add(arr2, (Object*)int3);

    // printf("arr 1 and arr 2 - %d\n", Object_EqualsTo((Object*)arr1, (Object*)arr2));

    // LinkedList* list = LinkedList_create();
    // LinkedList_print(list);
    // LinkedList_insertEnd(list, (Object*)int1);
    // LinkedList_insertEnd(list, (Object*)int2);
    // LinkedList_insertEnd(list, (Object*)int3);
    // LinkedList_print(list);
    // char* buf = Object_toString(LinkedList_at(list, 1));
    // printf("%s", buf);
    // free(buf);
    // printf("\n---------------------------------------\n");
    // LinkedList_insertStart(list, (Object*)int3);
    // LinkedList_print(list);
    // LinkedList_dtor(list);
    Integer_dtor(int1);
    Integer_dtor(int2);
    Integer_dtor(int3);
    Integer_dtor(int4);
}