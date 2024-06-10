#include "list.h"
#include "object.h"
#include <stdio.h>

int main(int argc, char** argv) {
    List* list = List_alloc();
    List_ctr(list);
    char* buf = Object_ToString((Object*)list);
    printf(buf);
}