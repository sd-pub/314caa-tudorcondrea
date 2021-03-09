#ifndef __STACK_H__
#define __STACK_H__

#include "LinkedList.h"

typedef struct {
    LinkedList *list;
} Stack;

void init_stack(Stack *stack);

int get_size_stack(Stack *stack);

int is_empty_stack(Stack *stack);

void* peek_stack(Stack *stack);

void pop_stack(Stack *stack);

void push_stack(Stack *stack, void *new_data);

void clear_stack(Stack *stack);

void purge_stack(Stack *stack);

#endif /* __STACK_H__ */