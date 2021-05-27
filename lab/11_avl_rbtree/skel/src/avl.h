/* Laborator 11 SD - AVL / Red-Black
 * Authors:
 *
 * Andrei Topala - topala.andrei@gmail.com
 * Dorin Geman  - doringeman@gmail.com
 * Teodor Dutu - teodor.dutu@gmail.com
 *
 * SD, 2021
 */

#ifndef AVL_H_
#define AVL_H_

typedef struct avl_node avl_node_t;
struct avl_node {
	void *data;
	int height;
	struct avl_node *left, *right;
};

typedef struct avl_tree avl_tree_t;
struct avl_tree {
	avl_node_t *root;
	int(*cmp)(const void*, const void*);
};


avl_tree_t *
avl_create(int (*cmp)(const void*, const void*));

void
avl_free(avl_tree_t *tree);

/**
 * Inserts data into the AVL tree.
 * 
 * @node: The tree to which to add the data.
 * @value: The data to be added into the AVL tree.
 * @data_size: The size of the above data in bytes.
 */
void
avl_insert(avl_tree_t *tree, void *value, size_t data_size);

/**
 * Finds a value in an AVL tree.
 * @return 1 if the value is in the tree; 0 otherwise.
 */
int
get_key(avl_tree_t *tree, void *value);

/**
 * Retrieves the maximum element in an AVL subtree.
 */
avl_node_t *
max_element(avl_tree_t *tree);

/**
 * Deletes a value from an AVL tree.
 * 
 * @node: The tree from which to delete the data.
 * @value: The data to be deleted from the AVL tree.
 */
void
avl_delete(avl_tree_t *tree, void *value);

void
preorder_traversal(avl_node_t *node);

#endif  /* AVL_H_ */
