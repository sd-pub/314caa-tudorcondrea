#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"

list_graph_t*
lg_create(int nodes)
{
	list_graph_t *lt = malloc(sizeof(*lt));
	lt->neighbors = malloc(nodes * sizeof(*lt->neighbors));
	for (int i = 0; i < nodes; i++)
		lt->neighbors[i] = ll_create(sizeof(int));
	lt->nodes = nodes;
	return lt;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	if (ll_has_int(graph->neighbors[src], dest) == 0)
	{
		ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
		ll_add_nth_node(graph->neighbors[dest], graph->neighbors[dest]->size, &src);
	}
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	if (ll_has_int(graph->neighbors[src], dest))
		return 1;
	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	int pos = ll_get_int_pos(graph->neighbors[src], dest);
	if (pos != -1)
	{
		ll_node_t *q = ll_remove_nth_node(graph->neighbors[src], pos);
		free(q->data);
		free(q);
	}
	pos = ll_get_int_pos(graph->neighbors[dest], src);
	if (pos != -1)
	{
		ll_node_t *q = ll_remove_nth_node(graph->neighbors[dest], pos);
		free(q->data);
		free(q);
	}
}

void
lg_free(list_graph_t* graph)
{
	for (int i = 0; i < graph->nodes; i++)
		ll_free(&graph->neighbors[i]);
	free(graph->neighbors);
	free(graph);
}