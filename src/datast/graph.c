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

Graph* Graph_alloc() {
    return (Graph*)malloc(sizeof(Graph));
}

void Graph_ctor(Graph* graph, size_t vc) {
    Object_ctor((Object*)graph, "Graph");
    graph->vCount = vc;
    graph->adj = calloc(vc, sizeof(*graph->adj));
    for(size_t i = 0; i < vc; i++) {
        graph->adj[i] = calloc(vc, sizeof(**graph->adj));
    }
}   

void Graph_dtor(Graph* graph) {
    Object_dtor((Object*)graph);
    for(size_t i = 0; i < graph->vCount; i++) {
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
    graph->adj[u][v] = 1;
    graph->eCount++;
}

void Graph_removeEdge(Graph* graph, size_t u, size_t v) {
    graph->adj[u][v] = 0;
    graph->eCount--;
}

long double Graph_BFS(Graph* graph, size_t u, size_t v) {
    
}

