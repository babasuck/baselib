#include "baselib.h"

#include "object_p.h"

#include <stdlib.h>
#include <stdio.h>

struct Graph {
    Object object;
    size_t vCount;
    size_t eCount;
    long double** adj;
};

struct GraphNode {
    Object object;
    Object* data;
};

Graph* Graph_alloc() {
    return (Graph*)malloc(sizeof(Graph));
}

void Graph_ctor(Graph* graph, size_t vc) {
    Object_ctor((Object*)graph, "Graph");
    graph->vCount = vc;
    graph->adj = malloc((vc + 1) * sizeof(*graph->adj));
    for(size_t i = 0; i <= vc; i++) {
        graph->adj[i] = malloc((vc + 1) *sizeof(**graph->adj));
    }
}   

void Graph_dtor(Graph* graph) {
    Object_dtor((Object*)graph);
    for(size_t i = 0; i <= graph->vCount; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
}

Graph* Graph_create(size_t vc) {
    Graph* graph = Graph_alloc();
    Graph_ctor(graph, vc);
    return graph;
}

void Graph_addEdge(Graph* graph, size_t u, size_t v) {
    if(u > graph->vCount || v > graph->vCount)
        return;
    graph->adj[u][v] = 1;
    graph->eCount++;
}

void Graph_removeEdge(Graph* graph, size_t u, size_t v) {
    graph->adj[u][v] = 0;
    graph->eCount--;
}

long double Graph_BFS(Graph* graph, size_t u, size_t v) {
    Queue* q = Queue_create();
    long double status = 0.0l;
    HashSet* visited = HashSet_create();

    Integer* startNode = Integer_create(u);
    Queue_Enqueue(q, (Object*)startNode);

    while(!Queue_isEmpty(q)) {
        Integer* n = (Integer*)Queue_Dequeue(q);
        size_t e = Integer_getInt(n);
        if (!HashSet_contains(visited, (Object*)n)) {
            HashSet_add(visited, (Object*)n);
            if (e == v) {
                status = 1.0l;
                break;
            }
            for(size_t i = 1; i <= graph->vCount; i++) {
                if(graph->adj[e][i] == 1) {
                    Integer* n = Integer_create(i);
                    if(!HashSet_contains(visited, (Object*)n)) {
                        Queue_Enqueue(q, (Object*)n);
                    } else {
                        Integer_dtor(n);
                    }
                }
            }
        }
    }
    HashSet_forAll(visited, (FuncForAll)Integer_dtor);
    while(!Queue_isEmpty(q)) {
        Integer_dtor((Integer*)Queue_Dequeue(q));
    }
    Queue_dtor(q);
    HashSet_dtor(visited);
    return status;
}

