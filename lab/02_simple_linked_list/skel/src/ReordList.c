#include <stdio.h>
#include "LinkedList.h"

int main()
{
    linked_list_t *list;
    list = ll_create(sizeof(int));
    int n, x, a, count = 0;
    scanf("%d%d\n", &n, &x);
    //read the list and count the numbers equal or less than x
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        if (a <= x)
            count++;
        ll_add_nth_node(list, i, &a);
    }
    //obtain the tail for pushing greater than x values to the end of the list
    ll_node_t *q = list->head, *tail;
    while (q->next != NULL)
        q = q->next;
    tail = q;
    //treat the head of the list separately due to lack of precedent node
    while (*(int*)list->head->data > x)
    {
        tail->next = list->head;
        list->head = list->head->next;
        tail = tail->next;
        tail->next = NULL;
    }
    int ok = 0;
    //stop when all counted numbers are arranged
    while (ok == 0)
    {
        ok = 1;
        q = list->head;
        for (int i = 0; i < count; i++)
            if (*(int *)q->next->data > x)
            {
                tail->next = q->next;
                tail = tail->next;
                q->next = q->next->next;
                tail->next = NULL;
                ok = 0;
            }
    }
    ll_print_int(list);
    ll_free(&list);
    return 0;
}
