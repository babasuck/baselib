#include "baselib.h"
#include "object.h"

#include <stdio.h>

int main(int argc, char** argv) {

    List* list = List_create();
    HashSet* hashSet = HashSet_create();

    Integer* integers[100];

    for(int i = 0; i < 100; i++) {
        Integer* inter = Integer_create(i);
        integers[i] = inter;
        //List_add(list, (Object*)inter);
        HashSet_add(hashSet, (Object*)inter);
    }

    HashSet_print(hashSet);

    for(int i = 0; i < 100; i++) {
        Integer_dtor(integers[i]);
    }

    List_dtor(list);
    HashSet_dtor(hashSet);
}