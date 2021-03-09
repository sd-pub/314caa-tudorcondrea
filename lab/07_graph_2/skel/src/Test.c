#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"

#define MAX_NODES 100

void dfs_connected_comps(ListGraph *lg, int *node, int *visited, LinkedList *component) {
    /* TODO */
}

void connected_components(ListGraph *lg, int *nodes_index) {
    /* TODO */
}

void dfs_topo_sort(ListGraph *lg, int *node, int *visited, LinkedList *result) {
    /* TODO */
}

void topo_sort(ListGraph *lg, int *nodes_index) {
    /* TODO */
}

void min_path(ListGraph *lg, int *nodes_index) {
    /* TODO */
}

int check_bipartite(ListGraph *lg, int *nodes_index, int *color) {
    /* TODO */
}

int main() {
    int nodes, edges;
    int color[MAX_NODES];
    int nodes_index[MAX_NODES];
    int x[MAX_NODES], y[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));

    scanf("%d %d", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    /* Ex 1 */
    connected_components(lg, nodes_index);

    /* Ex 2 */
    topo_sort(lg, nodes_index);

    /* Ex 3 */
    min_path(lg, nodes_index);

    /* Ex 4 */
    if (check_bipartite(lg, nodes_index, color)) {
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 1) {
                printf("%d ", i);
            }
        } 
        printf("\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 0) {
                printf("%d ", i);
            }
        } 
        printf("\n");
    } else {
        printf("The graph is not bipartite\n");
    }

    clear_list_graph(lg);
    free(lg);
    return 0;
}