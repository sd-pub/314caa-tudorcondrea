/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Binary Search Tree structure and function definitions
 */

#ifndef __BST_H_
#define __BST_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BST_DATA_LEN    50

typedef struct bst_node_t bst_node_t;
struct  bst_node_t {
    /* left child */
    bst_node_t *left;

    /* right child */
    bst_node_t *right;

    /* data contained by the node */
    char        *data;
};

typedef struct bst_tree_t bst_tree_t;
struct bst_tree_t {
    /* root of the tree */
    bst_node_t  *root;

    /* function used for sorting the keys */
    int	(*cmp)(const char *key1, const char *key2);
};

/**
 * Alloc memory for a new BST
 * @cmp_f: pointer to a function used for sorting
 * @return: pointer to the newly created BST
 */
bst_tree_t *bst_tree_create(int (*cmp_f) (const char *, const char *));

/**
 * Insert a new element in a BST
 * @bst_tree: the BST where to insert the new element
 * @data: the team to be inserted in BST
 */
void bst_tree_insert(bst_tree_t *bst_tree, char *data);

/**
 * Remove an element from a BST
 * @bst_tree: the BST where to remove from the element
 * @data: the data that is contained by the node which has to be removed
 */
void bst_tree_remove(bst_tree_t *bst_tree, char *data);

/**
 * Free a BST
 * @bst_tree: the BST to be freed
 */
void bst_tree_free(bst_tree_t *bst_tree);

#endif
