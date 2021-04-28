#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f
#define MAX_CHAR_LEN 50

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(
	list_graph_t *lg,
	int node,
	int *visited,
	linked_list_t *component
) {
	stack_t *stack = st_create(sizeof(int));
	visited[node] = 1;
	int n = 1;
	st_push(stack, &node);
	ll_add_nth_node(component, 0, &node);
	while (!st_is_empty(stack))
	{
		for (ll_node_t *q = lg->neighbors[*(int*)st_peek(stack)]->head; q != NULL; q = q->next)
		{
			if (visited[*(int*)q->data] == 0)
			{
				st_push(stack, q->data);
				visited[*(int*)q->data] = 1;
				ll_add_nth_node(component, n, q->data);
				n++;
			}
		}
		st_pop(stack);
	}
	st_free(stack);
}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");
	int i;
	*num_comp = 0;
	for (i = 0; i < lg->nodes; i++)
		if (visited[i] == 0)
		{
			comps[*num_comp] = ll_create(sizeof(int));
			dfs_connected_comps(lg, i, visited, comps[*num_comp]);
			*num_comp += 1;
		}
	return comps;
}

static void
dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	visited[node] = 1;
	for (ll_node_t *q = lg->neighbors[node]->head; q != NULL; q = q->next)
		if (visited[*(int*)q->data] == 0)
			dfs_topo_sort(lg, *(int*)q->data, visited, sorted);
	ll_add_nth_node(sorted, 0, &node);
}

static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	
	for (int i = 0; i < lg->nodes; i++)
		if (visited[i] == 0)
			dfs_topo_sort(lg, i, visited, sorted);

	return sorted;
}

static void
min_path(list_graph_t *lg, int start, int *dist)
{
	dist[start] = 0;
	queue_t *queue = q_create(sizeof(int), lg->nodes);
	q_enqueue(queue, &start);
	int visited[MAX_NODES] = {0};
	visited[start] = 1;
	while (!q_is_empty(queue))
	{
		for (ll_node_t *q = lg->neighbors[*(int*)q_front(queue)]->head; q != NULL; q = q->next)
		{
			if (visited[*(int*)q->data] == 0)
			{
				q_enqueue(queue, q->data);
				dist[*(int*)q->data] = dist[*(int*)q_front(queue)] + 1;
				visited[*(int*)q->data] = 1;
			}
		}
		q_dequeue(queue);
	}
	q_free(queue);
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	/* TODO: multimile vor avea culorile 1, respectiv 2 */
	return 0;
}

static void
test_connected_comp(void)
{
	unsigned int num_comps, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("Gaming clans problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("%d\n", num_comps);
	for (i = 0; i != num_comps; ++i) {
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}

	free(comps);
	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges, queries;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;
	stack_t *st = st_create(sizeof(int));

	printf("Cities courier distance problem:\n");
	scanf("%u %u %u", &nodes, &edges, &queries);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (unsigned int j = 0; j < queries; j++)
	{
		scanf("%d %d", &x, &y);
		for (i = 0; i != nodes; ++i)
			dist[i] = INF;
		min_path(lg, x, dist);
		if (dist[y] == INF)
			printf("N/A");
		else
		{
			while (dist[y] != 0)
			{
				st_push(st, &y);
				int found = 0;
				for (i = 0; i < nodes && found == 0; i++)
					if (dist[i] == dist[y] - 1 && lg_has_edge(lg, i, y))
					{
						found = 1;
						y = i;
					}
			}
			printf("%d ", y);
			while (!st_is_empty(st))
			{
				printf("%d ", *(int*)st_peek(st));
				st_pop(st);
			}
		}
		printf("\n");
	}

	lg_free(lg);
	st_free(st);
}

static void
test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int
main(void)
{
	/* Ex 1 */
	test_connected_comp();

	/* Ex 2 */
	//test_topo_sort();
	printf("\n");

	/* Ex 3 */
	test_min_dist();

	/* Ex 4 */
	//test_bipartite();

	return 0;
}
