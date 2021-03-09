/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Binary Tree structure and function definitions
 */ 

#ifndef __BINARY_TREE_H_
#define __BINARY_TREE_H_

typedef struct b_node_t b_node_t;
struct b_node_t {
    /* left child */
    b_node_t *left;
    /* right child */
    b_node_t *right;

    /* data contained by the node */
    int *data;
};

typedef struct b_tree_t b_tree_t;
struct b_tree_t {
    /* root of the tree */
    b_node_t *root;
};

/**
 * Creates a new binary tree
 * @return: pointer to the newly created tree
 */
b_tree_t *b_tree_create();

/**
 * Creates a new node with the specific data and adds it to the binary tree
 * @b_tree: the tree where the value is going to be inserted
 * @data: the value to insert in the tree
 */
void b_tree_insert(b_tree_t *b_tree, int data);

/**
 * Print a binary tree - preorder traversal
 * @b_tree: the binary tree to be printed
 */
void b_tree_print_preorder(b_tree_t *b_tree);

/**
 * Print a binary tree - inorder traversal
 * @b_tree: the binary tree to be printed
 */
void b_tree_print_inorder(b_tree_t *b_tree);

/**
 * Print a binary tree - postorder traversal
 * @b_tree: the binary tree to be printed
 */
void b_tree_print_postorder(b_tree_t *b_tree);

/**
 * Clear the whole memory used by the tree and its nodes
 * @b_tree: the binary tree to be freed
 */
void b_tree_free(b_tree_t *b_tree);

#endif
