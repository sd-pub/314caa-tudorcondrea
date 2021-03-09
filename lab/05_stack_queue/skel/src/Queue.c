#include <stdlib.h>

#include "Queue.h"

void init_q(struct Queue *q) {
    q->list = malloc(sizeof(struct LinkedList));
    init_list(q->list);
}

int get_size_q(struct Queue *q) {
    /* TODO */
}

int is_empty_q(struct Queue *q) {
    /* TODO */
}

void* front(struct Queue *q) {
    /* TODO */
}

void dequeue(struct Queue *q) {
    /* TODO */
}

void enqueue(struct Queue *q, void *new_data) {
    /* TODO */
}

void clear_q(struct Queue *q) {
    /* TODO */
}

void purge_q(struct Queue *q) {
    /* TODO */
}