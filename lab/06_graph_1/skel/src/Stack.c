#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

void init_stack(Stack *stack) {
    stack->list = malloc(sizeof(LinkedList));
    if (stack == NULL) {
        perror("Not enough memory to initialize the queue!");
        exit(-1);
    }

    init_list(stack->list);
}

int get_size_stack(Stack *stack) {
    return stack->list->size;
}

int is_empty_stack(Stack *stack) {
    return get_size_stack(stack) == 0;
}

void* peek_stack(Stack *stack) {
    if (stack == NULL || stack->list == NULL) {
        return NULL;
    }

    return stack->list->tail->data;
}

void pop_stack(Stack *stack) {
    struct Node *node;

    if (stack == NULL || stack->list == NULL) {
        return;
    }

    node = remove_nth_node(stack->list, stack->list->size - 1);
    free(node);
}

void push_stack(Stack *stack, void *new_data) {
    add_nth_node(stack->list, stack->list->size, new_data);
}

void clear_stack(Stack *stack) {
    struct Node *node;
    while (!is_empty_stack(stack)) {
        node = remove_nth_node(stack->list, 0);
        free(node);
    }
}

void purge_stack(Stack *stack) {
    clear_stack(stack);
    free(stack->list);
}