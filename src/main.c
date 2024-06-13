#include "baselib.h"
#include "object.h"

#include <stdio.h>

int main(int argc, char** argv) {

    Integer* int1 = Integer_create(1);
    Integer* int2 = Integer_create(2);
    Integer* int3 = Integer_create(3);
    Integer* int4 = Integer_create(4);
    Integer* int5 = Integer_create(5);

    List* list = List_create();

    List_add(list, (Object*)int1);
    List_add(list, (Object*)int2);
    List_add(list, (Object*)int3);
    List_add(list, (Object*)int4);
    List_add(list, (Object*)int5);

    HashSet* hashSet = HashSet_create();
    HashSet_add(hashSet, (Object*)int1);
    HashSet_add(hashSet, (Object*)int2);
    HashSet_add(hashSet, (Object*)int3);
    HashSet_add(hashSet, (Object*)int4);

    Integer_dtor(int1);
    Integer_dtor(int2);
    Integer_dtor(int3);
    Integer_dtor(int4);
    Integer_dtor(int5);
    List_dtor(list);
    HashSet_dtor(hashSet);
}