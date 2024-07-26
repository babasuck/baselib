#include "baselib.h"

#include <stdio.h>

int main(int argc, char** argv) {

    Primitive* doubletest = Primitive_create(3.14);
    
    Integer* int1 = Integer_create(1);
    Integer* int2 = Integer_create(2);
    Integer* int3 = Integer_create(3);
    Integer* int4 = Integer_create(1);

    //printf("int 1 and int 2 - %d\n", Object_EqualsTo(int1, int2));

    // HashMap* hm = HashMap_create();
    // HashMap_add(hm, "Avocado", (Object*)int1);
    // HashMap_add(hm, "Apple", (Object*)int2);
    // HashMap_add(hm, "Orange", (Object*)int3);
    // HashMap_add(hm, "Banana", (Object*)int3);

    // HashMap_print(hm);

    // //printf("El - %s\n", Object_toString(HashMap_get(hm, "Apple")));

    // HashMap_dtor(hm);

    printf("\nQueue ctor\n\n");

    Queue* q = Queue_create();
    Queue_Enqueue(q, (Object*)int1);
    Queue_Enqueue(q, (Object*)int2);
    Queue_Enqueue(q, (Object*)int3);

    Queue_Dequeue(q);

    Queue_print(q);

    Graph* graph = Graph_create(5);
    Graph_addEdge(graph, 1, 2);
    Graph_addEdge(graph, 2, 5);
    Graph_addEdge(graph, 5, 3);
    printf("BFS - %lf\n", Graph_BFS(graph, 1, 3));

    printf("\nGraph dtor\n\n");

    Graph_dtor(graph);

    printf("\nQueue dtor\n\n");

    Queue_dtor(q);

    printf("\nInteger dtor\n\n");

    Integer_dtor(int1);
    Integer_dtor(int2);
    Integer_dtor(int3);
    Integer_dtor(int4);
}