#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include "LinkedList.h"

typedef struct {
    LinkedList **neighbors;       /* Listele de adiacenta ale grafului */
    int nodes;                    /* Numarul de noduri din graf. */
} ListGraph;

void init_list_graph(ListGraph *graph, int nodes);

void add_edge_list_graph(ListGraph *graph, int src, int *dest);

int has_edge_list_graph(ListGraph *graph, int src, int dest);

LinkedList* get_neighbours_list_graph(ListGraph *graph, int node);

void remove_edge_list_graph(ListGraph *graph, int src, int dest);

void clear_list_graph(ListGraph *graph);

#endif /* __LISTGRAPH_H__ */