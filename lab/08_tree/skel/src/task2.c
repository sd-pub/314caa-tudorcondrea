/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */

#include "binary_tree.h"
#include "linkedlist.h"

void copy_nodes(b_node_t *source, b_node_t **dest, size_t data_size)
{
    *dest = malloc(sizeof(b_node_t));
    (*dest)->data = malloc(data_size);
    (*dest)->left = (*dest)->right = NULL;
    memcpy((*dest)->data, source->data, data_size);

    if (source->left != NULL)
        copy_nodes(source->left, &(*dest)->left, data_size);
    if (source->right != NULL)
        copy_nodes(source->right, &(*dest)->right, data_size);
}

b_tree_t *b_tree_copy(b_tree_t *source)
{
    b_tree_t *dest = b_tree_create(source->data_size);
    copy_nodes(source->root, &dest->root, source->data_size);
    return dest;
}

void tree_sum(b_node_t *node, int delta, int *max)
{
    delta += *(int*)node->data;
    if (delta > *max)
        *max = delta;
    if (node->left)
        tree_sum(node->left, delta, max);
    if (node->right)
        tree_sum(node->right, delta, max);
}

void print_dist_trav(b_node_t *node, int dist, int target, LinkedList *list)
{
    add_nth_node(list, list->size, node->data);
    dist += *(int*)node->data;
    if (dist == target)
        print_int_linkedlist(list);
    if (node->left)
        print_dist_trav(node->left, dist, target, list);
    if (node->right)
        print_dist_trav(node->right, dist, target, list);
    Node *rem_node = remove_nth_node(list, list->size - 1);
    free(rem_node);
}

void print_function(void *arg)
{
    printf("%d ", *(int*)arg);
}

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

int main(void)
{
    b_tree_t *tree = b_tree_create(sizeof(int));
    read_tree(tree);
    b_tree_t *aux_tree = b_tree_copy(tree);
    int max = 0;
    LinkedList *trav;
    trav = malloc(sizeof(*trav));
    init_list(trav);
    tree_sum(aux_tree->root, 0, &max);
    printf("%d\n", max);
    print_dist_trav(aux_tree->root, 0, max, trav);
    free_list(&trav);
    b_tree_free(tree, free);
    b_tree_free(aux_tree, free);
    return 0;
}
