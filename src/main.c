#include "baselib.h"
#include "object.h"

#include <stdio.h>

#define ARRSIZE 10

int main(int argc, char** argv) {

    List* list = List_create();

    HashSet* hashSet = HashSet_create();

    Integer* integers[ARRSIZE];

    for(int i = 0; i < ARRSIZE; i++) {
        Integer* inter = Integer_create(i);
        integers[i] = inter;
        List_add(list, (Object*)inter);
        HashSet_add(hashSet, (Object*)inter);
    }

    List* list2 = (List*)Object_clone((Object*)list);
    List_print(list);
    printf("\n----------------------------------\n");
    List_print(list2);
    //HashSet_print(hashSet);

    for(int i = 0; i < ARRSIZE; i++) {
        Integer_dtor(integers[i]);
    }

    List_dtor(list);
    HashSet_dtor(hashSet);
}