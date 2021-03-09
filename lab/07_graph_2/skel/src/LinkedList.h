#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct Node {
    void *data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un pointer la void. */
    struct 
    Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

void init_list(LinkedList *list);

/*
 * Acestea sunt functiile pe care trebuie sa le implementam.
 * Implementarea acestora se va face in LinkedList.c .
 */

void add_nth_node(LinkedList *list, int n, void *new_data);

Node* remove_nth_node(LinkedList *list, int n);

int get_size(LinkedList *list);

void free_list(LinkedList **list);

void print_int_linkedlist(LinkedList *list);

void print_string_linkedlist(LinkedList *list);

#endif /* __LINKEDLIST_H__ */