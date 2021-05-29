#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t * linked_list = malloc(sizeof(linked_list_t));
    DIE(linked_list == NULL, "Not enough memory\n");
    linked_list->data_size = data_size;
    linked_list->size = 0;
    linked_list->head = NULL;
    return linked_list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    if (n < 0)
    {
        printf("Node index can't be negative\n");
        return;
    }
    if (n > list->size)
        n = list->size;
    ll_node_t * new_node;
    new_node = malloc(sizeof(ll_node_t));
    DIE(new_node == NULL, "Not enough memory\n");
    new_node->data = malloc(list->data_size);
    DIE(new_node->data == NULL, "Not enough memory\n");
    memcpy(new_node->data, new_data, list->data_size);
    if (list->size == 0)
    {
        list->head = new_node;
        list->head->next = NULL;
    }
    else
    {
        if (n == 0)
        {
            new_node->next = list->head;
            list->head = new_node;
        }
        else
        {
            ll_node_t * q = list->head;
            int i;
            for (i = 0; i < n - 1; i++)
                q = q->next;
            if (n == list->size)
                new_node->next = NULL;
            else
                new_node->next = q->next;
            q->next = new_node;
        }
        
    }
    list->size += 1;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    ll_node_t * elim_node, * q;
    if (n < 0)
    {
        printf("Node index can't be negative\n");
        return NULL;
    }
    if (list->size == 0)
    {
        printf("List is empty\n");
        return NULL;
    }
    if (n > list->size - 1)
        n = list->size - 1;
    if (n == 0)
    {
        elim_node = list->head;
        list->head = list->head->next;
    }
    else
    {
        int i;
        q = list->head;
        for (i = 0; i < n - 1; i++)
            q = q->next;
        elim_node = q->next;
        q->next = q->next->next;
    }
    list->size--;
    return elim_node;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void
ll_free(linked_list_t** pp_list)
{
    int i;
    linked_list_t * list = *pp_list;
    ll_node_t * q = list->head, *free_node;
    for (i = 0; i < list->size; i++)
    {
        free_node = q;
        q = q->next;
        free(free_node->data);
        free(free_node);
    }
    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    ll_node_t *q = list->head;
    for (q; q != NULL; q = q->next)
        printf("%d ", *(int *)q->data);
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    ll_node_t *q = list->head;
    for(q; q != NULL; q = q->next)
        printf("%s ", (char *)q->data);
    printf("\n");
}
