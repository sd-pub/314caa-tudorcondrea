#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

void init_stack(struct Stack *stack) {
    stack->list = malloc(sizeof(struct LinkedList));
    init_list(stack->list);
}

int get_size_stack(struct Stack *stack) {
    /* TODO */
}

int is_empty_stack(struct Stack *stack) {
    /* TODO */
}

void* peek_stack(struct Stack *stack) {
    /* TODO */
}

void pop_stack(struct Stack *stack) {
    /* TODO */
}

void push_stack(struct Stack *stack, void *new_data) {
    /* TODO */
}

void clear_stack(struct Stack *stack) {
    /* TODO */
}

void purge_stack(struct Stack *stack) {
    /* TODO */
}