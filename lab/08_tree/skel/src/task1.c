/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #1 - Binary Tree implementation (test file)
 */

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, data, N;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, data);
    }
}

int main(void)
{
    b_tree_t *binary_tree;

    binary_tree = b_tree_create();

    read_tree(binary_tree);

    b_tree_print_preorder(binary_tree);
    b_tree_print_inorder(binary_tree);
    b_tree_print_postorder(binary_tree);

    b_tree_free(binary_tree);

    return 0;
}
