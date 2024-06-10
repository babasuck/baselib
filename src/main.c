#include "list.h"
#include "object.h"
#include <stdio.h>

int main(int argc, char** argv) {
    List* list = List_alloc();
    List_ctr(list);

    List* list1 = List_alloc();
    List_ctr(list1);

    List* list2 = List_alloc();
    List_ctr(list2);

    List* list3 = List_alloc();
    List_ctr(list3);

    List* listOfLists = List_alloc();
    List_ctr(listOfLists);

    List_add(listOfLists, list);
    List_add(listOfLists, list1);
    List_add(listOfLists, list2);
    List_add(listOfLists, list3);
    List_print(listOfLists);

}