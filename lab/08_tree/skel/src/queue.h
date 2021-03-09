#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "linkedlist.h"

typedef struct {
    LinkedList *list;
} Queue;

void init_q(Queue *q);

int get_size_q(Queue *q);

int is_empty_q(Queue *q);

void* front(Queue *q);

void dequeue(Queue *q);

void enqueue(Queue *q, void *new_data);

void clear_q(Queue *q);

void purge_q(Queue *q);

#endif /* __QUEUE_H__ */