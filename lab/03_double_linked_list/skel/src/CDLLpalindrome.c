#include <stdio.h>
#include "CircularDoublyLinkedList.h"

int main()
{
    doubly_linked_list_t * list = dll_create(sizeof(char));
    int n;
    char c;
    //read n characters from stdin
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%c", &c);
        dll_add_nth_node(list, i, &c);
    }
    //start at both ends and go towards the middle checking for discrepancies
    dll_node_t *p, *q;
    p = q = list->head;
    q = q->prev;
    int ok = 1;
    for (int i = 0; i < list->size / 2; i++)
    {
        if (*(char *)q->data != *(char *)p->data)
            ok = 0;
        q = q->prev;
        p = p->next;
    }
    if (ok == 0)
        printf("nu ");   
    printf("este palindrom\n");
    dll_free(&list);
    return 0;
}