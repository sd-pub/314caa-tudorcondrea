#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "LinkedList.h"

struct Queue {
    struct LinkedList *list;
};

void init_q(struct Queue *q);

int get_size_q(struct Queue *q);

int is_empty_q(struct Queue *q);

void* front(struct Queue *q);

void dequeue(struct Queue *q);

void enqueue(struct Queue *q, void *new_data);

void clear_q(struct Queue *q);

void purge_q(struct Queue *q);

#endif /* __QUEUE_H__ */