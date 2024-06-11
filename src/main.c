#include "baselib.h"
#include "object.h"
#include <stdio.h>

int main(int argc, char** argv) {
    Integer* int1 = Integer_alloc();
    Integer* int2 = Integer_alloc();
    Integer* int3 = Integer_alloc();
    Integer* int4 = Integer_alloc();
    Integer* int5 = Integer_alloc();

    Integer_ctor(int1, 1);
    Integer_ctor(int2, 2);
    Integer_ctor(int3, 3);
    Integer_ctor(int4, 4);
    Integer_ctor(int5, 5);

    List* list = List_alloc();
    List_ctor(list);

    List_add(list, (Object*)int1);
    List_add(list, (Object*)int2);
    List_add(list, (Object*)int3);
    List_add(list, (Object*)int4);
    List_add(list, (Object*)int5);

    HashSet* hashSet = HashSet_alloc();
    HashSet_ctor(hashSet); 
    HashSet_add(hashSet, (Object*)int1);
    HashSet_add(hashSet, (Object*)int2);
    HashSet_add(hashSet, (Object*)int3);
    HashSet_add(hashSet, (Object*)int4);

    printf("%d", HashSet_contains(hashSet, int5));


}