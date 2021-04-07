#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *
st_create(unsigned int data_size)
{
	stack_t *stack = malloc(sizeof(stack_t));
	stack->list = ll_create(data_size);
	return stack;
}

unsigned int
st_get_size(stack_t *st)
{
	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	if (ll_get_size(st->list) == 0)
		return 1;
	return 0;
}

void *
st_peek(stack_t *st)
{
	if (!st)
		return NULL;
	return st->list->head->data;
}

void
st_pop(stack_t *st)
{
	ll_node_t *q = ll_remove_nth_node(st->list, 0);
	free(q->data);
	free(q);
}

void
st_push(stack_t *st, void *new_data)
{
	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	int n = st->list->size;
	while(n > 0)
	{
		st_pop(st);
		n--;
	}
}

void
st_free(stack_t *st)
{
	st_clear(st);
	free(st->list);
	free(st);
}
