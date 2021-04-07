#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *queue = malloc(sizeof(queue_t));
	queue->data_size = data_size;
	queue->max_size = max_size;
	queue->size = 0;
	// Bufferul e folosit ca un vector de orice tip de data
	queue->buff = malloc(max_size * data_size);
	queue->read_idx = 0;
	queue->write_idx = 0;
	return queue;
}

unsigned int
q_get_size(queue_t *q)
{
	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	if (q->size == 0)
		return 1;
	return 0;
}

void *
q_front(queue_t *q)
{
	// Folosesc cel mai mic tip de date pentru a ma putea plimba
	// cu cati bytes am nevoie dupa tipul de date cerut 
	if (!q_is_empty(q))
		return (char*)q->buff + q->read_idx * q->data_size;
	return NULL;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	if (q_is_empty(q))
		return false;
	// Pentru a mentine O(1), dau loop prin vector folosind 2 indecsi
	q->read_idx++;
	q->read_idx %= q->max_size;
	q->size--;
	return true;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	if (q_get_size(q) == q->max_size)
		return false;
	memcpy((char*)q->buff + q->write_idx * q->data_size, new_data, q->data_size);
	q->size++;
	q->write_idx++;
	q->write_idx %= q->max_size;
	return true;
}

void
q_clear(queue_t *q)
{
	int n = q_get_size(q);
	while(n > 0)
	{
		q_dequeue(q);
		n--;
	}
}

void
q_free(queue_t *q)
{
	free(q->buff);
	free(q);
}
