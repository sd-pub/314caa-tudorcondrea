#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

typedef struct {
    int **matrix;       /* Matricea de adiacenta a grafului */
    int nodes;          /* Numarul de noduri din graf. */
} MatrixGraph;

void init_matrix_graph(MatrixGraph *graph, int nodes);

void add_edge_matrix_graph(MatrixGraph *graph, int src, int dest);

int has_edge_matrix_graph(MatrixGraph *graph, int src, int dest);

void remove_edge_matrix_graph(MatrixGraph *graph, int src, int dest);

void clear_matrix_graph(MatrixGraph *graph);

#endif /* __MATRIXGRAPH_H__ */