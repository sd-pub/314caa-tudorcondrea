#include <stdlib.h>
#include <stdio.h>

#include "ListGraph.h"

void init_list_graph(ListGraph *graph, int nodes) {
    graph->nodes = nodes;
    graph->neighbors = malloc(nodes * sizeof(LinkedList));

    if (graph->neighbors == NULL) {
        perror("Not enough memory to initialize the adjacency list!");
        exit(-1);
    }

    for (int i = 0; i < nodes; ++i) {
        graph->neighbors[i] = malloc(sizeof(LinkedList));

        if (graph->neighbors[i] == NULL) {
            perror("Not enough memory to initialize the adjacency list!");
            exit(-1);
        }
        init_list(graph->neighbors[i]);
    }
}

void add_edge_list_graph(ListGraph *graph, int src, int *dest) {
    add_nth_node(graph->neighbors[src], (1 <<30), dest);
}

int has_edge_list_graph(ListGraph *graph, int src, int dest) {
    Node *head = graph->neighbors[src]->head;
    int crt_node;

    while (head != NULL) {
        crt_node = *(int *)head->data;

        if (crt_node == dest) {
            return 1;
        }
        head = head->next;
    }

    return 0;
}

LinkedList* get_neighbours_list_graph(ListGraph *graph, int node) {
    return graph->neighbors[node];
}

void remove_edge_list_graph(ListGraph *graph, int src, int dest) {
    Node *head = graph->neighbors[src]->head;
    int node_index = 0;
    int crt_node = 0;

    while (head != NULL) {
        crt_node = *(int *)head->data;

        if (crt_node == dest) {
            remove_nth_node(graph->neighbors[src], node_index);
            return;
        }
        head = head->next;
        ++node_index;
    }
}

void clear_list_graph(ListGraph *graph) {
    for (int i = 0; i < graph->nodes; ++i) {
        free_list(&graph->neighbors[i]);
    }
    free(graph->neighbors);
}
