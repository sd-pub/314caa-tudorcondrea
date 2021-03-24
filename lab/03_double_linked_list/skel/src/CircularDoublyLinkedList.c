#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t * list = malloc(sizeof(doubly_linked_list_t));
    DIE(list == NULL, "Couldn't allocate memory\n");
    list->data_size = data_size;
    list->size = 0;
    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if (n < 0)
        return NULL;
    n %= list->size;
    dll_node_t * q = list->head;
    for (int i = 0; i < n; i++)
        q = q->next;
    return q;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    if (n < 0)
    {
        return;
    }
    if (n >= list->size)
        n = list->size;
    dll_node_t * new_node = malloc(sizeof(dll_node_t));
    DIE(new_node == NULL, "Couldn't allocate memory\n");
    new_node->data = malloc(list->data_size);
    DIE(new_node->data == NULL, "Couldn't allocate memory\n");
    memcpy(new_node->data, data, list->data_size);
    if (n == 0)
    {
        if (list->size == 0)
        {
            list->head = new_node;
            new_node->next = new_node->prev = new_node;
        }
        else
        {
            new_node->prev = list->head->prev;
            list->head->prev->next = new_node;
            new_node->next = list->head;
            list->head->prev = new_node;
            list->head = list->head->prev;
        }
    }
    else
    {
        dll_node_t * q = list->head;
        for (int i = 0; i < n - 1; i++)
            q = q->next;
        new_node->prev = q;
        new_node->next = q->next;
        q->next->prev = new_node;
        q->next = new_node;
    }
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    if (n < 0)
        return NULL;
    if (n >= list->size - 1)
        n = list->size - 1;
    if (list->size == 0)
        return NULL;
    dll_node_t * ret_node, * q;
    if (n == 0)
    {
        ret_node = list->head;
        list->head->prev->next = list->head->next;
        list->head->next->prev = list->head->prev;
        list->head = list->head->next;
    }
    else
    {
        q = list->head;
        for (int i = 0; i < n - 1; i++)
            q = q->next;
        ret_node = q->next;
        q->next = q->next->next;
        q->next->prev = q;
    }
    list->size--;
    return ret_node;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    dll_node_t * q = (*pp_list)->head;
    for (int i = 0; i < (*pp_list)->size; i++)
    {
        (*pp_list)->head = (*pp_list)->head->next;
        free(q->data);
        free(q);
        q = (*pp_list)->head;
    }
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    dll_node_t *q = list->head;
    for (int i = 0; i < list->size; i++)
    {
        printf("%d ", *(int*)q->data);
        q = q->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
    dll_node_t *q = list->head;
    for (int i = 0; i < list->size; i++)
    {
        printf("%s ", (char*)q->data);
        q = q->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_left_circular(dll_node_t* start)
{
    dll_node_t *q = start;
    do
    {
        printf("%d ", *(int *)q->data);
        q = q->prev;
    } while (q != start);
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    dll_node_t *q = start;
    do
    {
        printf("%d ", *(int *)q->data);
        q = q->next;
    } while (q != start);
    printf("\n");
}
