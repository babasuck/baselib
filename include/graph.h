#pragma once

typedef struct Graph Graph;

Graph* Graph_alloc();
void Graph_ctor(Graph* graph, size_t vc);
void Graph_dtor(Graph* graph);
Graph* Graph_create(size_t vc);

void Graph_addEdge(Graph* graph, size_t u, size_t v);
void Graph_removeEdge(Graph* graph, size_t u, size_t v)
