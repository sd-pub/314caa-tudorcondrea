#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"

#define MAX_NODES 10

void print_matrix_graph(MatrixGraph *g) {
    /* TODO */
}

void print_list_graph(ListGraph *g) {
    /* TODO */
}

void dfs_list_graph(ListGraph *lg, int node, int *color, int *t_desc, int *t_tin) {
    /* TODO */
}

void dfs_matrix_graph(MatrixGraph *lg, int node, int *color, int *t_desc, int *t_tin) {
    /* TODO */
}

void bfs_list_graph(ListGraph *lg, int node, int *color, int *parent) {
    /* TODO */
}

void bfs_matrix_graph(MatrixGraph *lg, int node, int *color, int *parent) {
    /* TODO */
}

void floyd_warshall(MatrixGraph *lg) {
    /* TODO BONUS */
}

int main() {
    int nodes, edges;
    int x[MAX_NODES], y[MAX_NODES];
    int color[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));
    MatrixGraph *mg = malloc(sizeof(MatrixGraph));

    scanf("%d %d", &nodes, &edges);

    init_list_graph(lg, nodes);
    init_matrix_graph(mg, nodes);

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_matrix_graph(mg, x[i], y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    clear_list_graph(lg);
    clear_matrix_graph(mg);
    free(lg);
    free(mg);
    return 0;
}