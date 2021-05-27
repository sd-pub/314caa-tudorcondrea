/**
 * SD, 2021
 * 
 * Lab #9, BST & Heap
 * 
 * Task #2 - Heap implementation
 */

#include "heap.h"
#include "utils.h"

heap_t *heap_create(int (*cmp_f)(const team_t *, const team_t *))
{
    heap_t *heap;

    heap = malloc(sizeof(*heap));
    DIE(heap == NULL, "heap malloc");

    heap->cmp       = cmp_f;
    heap->size      = 0;
    heap->capacity  = 2;
    heap->arr       = malloc(heap->capacity * sizeof(*heap->arr));
    DIE(heap->arr == NULL, "heap->arr malloc");

    return heap;
}

static void __heap_insert_fix(heap_t *heap, int pos)
{
    team_t *tmp_team;
    int p = GO_UP(pos);
    while (p >= 0 && pos >= 0 && heap->cmp(heap->arr[pos], heap->arr[p]) < 0)
    {
        tmp_team = heap->arr[p];
        heap->arr[p] = heap->arr[pos];
        heap->arr[pos] = tmp_team;
        pos = p;
        p = GO_UP(pos);
    }
}

void heap_insert(heap_t *heap, team_t *team)
{
    char *rc;

    heap->arr[heap->size] = malloc(sizeof(**heap->arr));
    DIE(heap->arr[heap->size] == NULL, "heap_insert malloc");

    heap->arr[heap->size]->name = calloc(TEAM_NAME_LEN,
            sizeof(*heap->arr[heap->size]->name));
    DIE(heap->arr[heap->size]->name == NULL, "heap_insert name calloc");

    rc = strncpy(heap->arr[heap->size]->name, team->name,
            TEAM_NAME_LEN - 1);
    DIE(rc != heap->arr[heap->size]->name, "heap_insert name strncpy");
    heap->arr[heap->size]->score = team->score;

    __heap_insert_fix(heap, heap->size);

    heap->size++;
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;

        heap->arr = realloc(heap->arr,
                heap->capacity * sizeof(*heap->arr));
        DIE(heap->arr == NULL, "heap->arr realloc");
    }
}

team_t *heap_top(heap_t *heap)
{
    return heap->arr[0];
}

static void __heap_pop_fix(heap_t *heap, int pos)
{
    team_t *tmp_team;
    int p = pos;
    int l = GO_LEFT(pos);
    int r = GO_RIGHT(pos);

    while (p < heap->size && l < heap->size && r < heap->size)
    {
        if (heap->cmp(heap->arr[l], heap->arr[r]) > 0)
        {
            tmp_team = heap->arr[r];
            heap->arr[r] = heap->arr[p];
            heap->arr[p] = tmp_team;
            p = r;
        }
        else if (heap->cmp(heap->arr[l], heap->arr[r]) < 0)
        {
            tmp_team = heap->arr[l];
            heap->arr[l] = heap->arr[p];
            heap->arr[p] = tmp_team;
            p = l;
        }
        l = GO_LEFT(p);
        r = GO_RIGHT(p);
    }
}

void heap_pop(heap_t *heap)
{
    free(heap->arr[0]->name);
    free(heap->arr[0]);

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    __heap_pop_fix(heap, 0);
}

int heap_empty(heap_t *heap)
{
    return heap->size <= 0;
}

void heap_free(heap_t *heap)
{
    for (int i = 0; i < heap->size; i++)
    {
        free(heap->arr[i]->name);
        free(heap->arr[i]);
    }
    free(heap->arr);
    free(heap);
}
