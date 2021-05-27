/* Laborator 11 SD - AVL / Red-Black
 * Authors:
 *
 * Andrei Topala - topala.andrei@gmail.com
 * Dorin Geman  - doringeman@gmail.com
 * Teodor Dutu - teodor.dutu@gmail.com
 *
 * SD, 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"


avl_tree_t*
avl_create(int (*cmp)(const void*, const void*))
{
	avl_tree_t *tree = malloc(sizeof(*tree));
	if (!tree)
		return NULL;
	
	tree->cmp = cmp;
	tree->root = NULL;

	return tree;
}

void
node_free(avl_node_t **node)
{
	avl_node_t *temp = *node;
	if (!temp)
		return;	

	if (temp->left)
		node_free(&temp->left);
	if (temp->right)
		node_free(&temp->right);

	if (!temp->left && temp->right) {
		free(temp->data);
		free(temp);
		(*node) = NULL;

		return;
	}
}

void
avl_free(avl_tree_t *tree)
{
	if (tree->root)
		node_free(&tree->root);
	free(tree);
}

static int
__max(int a, int b)
{
	return a > b ? a : b;
}

/**
 * Creates an AVL node. 
 * @value: The value to be inserted into the node.
 * @data_size: The size in bytes of the above value.
 */
static avl_node_t *
__node_create(void *value, size_t data_size)
{
	avl_node_t *node = malloc(sizeof(*node));
	if (node == NULL)
		return NULL;

	node->data = malloc(data_size);
	if (!node->data) {
		free(node);
		return NULL;
	}

	memcpy(node->data, value, data_size);

	/* Leaf nodes have a height of 0. */
	node->height = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/**
 * NULL nodes have a height of -1 in order for the rule below to hold:
 * node->height = 1 + max(node->left->height, nod->right->height)
 */
static int
__height(avl_node_t *node)
{
	return node ? node->height : -1;
}

/**
 * Rotate node to the right.
 *
 *      node  			    lson
 *     /    \			   /    \ 
 *   lson    y    --->    x    node
 *   /  \     		           /   \ 
 *  x   lrson                lrson  y
 */
static void
__rotate_right(avl_node_t **node) {
	avl_node_t *lson = (*node)->left;
	avl_node_t *lrson = lson->right;
	avl_node_t *rson = (*node);

	(*node) = lson;
	(*node)->right = rson;
	(*node)->right->left = lrson;

	/* Fix height. */
	(*node)->right->height = 1 + __max(__height((*node)->right->left),
		__height((*node)->right->right));
	(*node)->height = 1 + __max(__height((*node)->left),
		__height((*node)->right));

}

/**
 * Rotate node to the left.
 *
 *     node  			    rson
 *    /    \			   /    \ 
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */	
static void
__rotate_left(avl_node_t **node) {
	avl_node_t *rson = (*node)->right;
	avl_node_t *rlson = rson->left;
	avl_node_t *lson = (*node);
	
	(*node) = rson;
	(*node)->left = lson;
	(*node)->left->right = rlson;

	/* Fix height. */
	(*node)->left->height = 1 + __max(__height((*node)->left->left),
		__height((*node)->left->right));
	(*node)->height = 1 + __max(__height((*node)->left),
		__height((*node)->right));

}

/**
 * Rebalances the AVL tree.
 */
static void
__avl_fix(avl_node_t **node)
{
	/* TODO: Add the necessary rotations. */
	if (__height((*node)->left) > __height((*node)->right) + 1 
			&& __height((*node)->left->left)
				>= __height((*node)->left->right)) {
		/* TODO: RR rotation.
		 *
		 *     node                  a
		 *     /                    / \
		 *    a          --->      b   node
		 *   /
		 *  b
		 *
		 */
		__rotate_right(node);
	} else if (__height((*node)->right) > __height((*node)->left) + 1 
			&& __height((*node)->right->right)
				>= __height((*node)->right->left)) {
		/* TODO: LL rotation.
		 *
		 *     node                a
		 *        \               / \
		 *         a     --->  node  b
		 *          \ 
		 *           b
		 *
		 */
		__rotate_left(node);
	} else if (__height((*node)->left) > __height((*node)->right) + 1 
			&& __height((*node)->left->left)
				< __height((*node)->left->right)) {
		/* TODO: LR rotation.
		 *
		 *     node                node               b
		 *     /        left       /      right      / \
		 *    a         --->      b        --->     a   node
		 *     \                 /
		 *      b               a
		 *
		 */
		__rotate_left(&(*node)->left);
		__rotate_right(&(*node));
	} else if (__height((*node)->right) > __height((*node)->left) + 1 
			&& __height((*node)->right->right)
				< __height((*node)->right->left)) {
		/* TODO: RL rotation.
		 *
		 *     node                node                  b
		 *        \      right        \       left      / \
		 *         a      --->         b       --->   node a
		 *        /                     \
		 *       b                       a
		 *
		 */
		__rotate_right(&(*node)->right);
		__rotate_left(node);
	}
}

/**
 * Inserts data into an AVL subtree.
 * 
 * @node: The root of the current subtree.
 * @value: The data to be added into the subtree.
 * @data_size: The size of the above data in bytes.
 * @cmp: The function that compares data in the AVL tree.
 */
static void
__avl_insert(avl_node_t **node, void *value, size_t data_size,
	int (*cmp)(const void*, const void*))
{
	if (!(*node))
	{
		*node = __node_create(value, data_size);
		return;
	}

	if (cmp((*node)->data, value) > 0)
	{
		__avl_insert(&(*node)->left, value, data_size, cmp);
	}
	else
	{
		__avl_insert(&(*node)->right, value, data_size, cmp);
	}

	(*node)->height = 1 + __max(__height((*node)->left), __height((*node)->right));
	__avl_fix(node);
}

void
avl_insert(avl_tree_t *tree, void *value, size_t data_size)
{
	if (tree)
		__avl_insert(&tree->root, value, data_size, tree->cmp);
}

/**
 * Finds a value in an AVL tree.
 * @node: The root of the current subtree.
 * @value: The data to be searched in the subtree.
 * @cmp: The function that compares data in the AVL tree.
 * @return 1 if the value is in the tree; 0 otherwise.
 */
static int
__get_key(avl_node_t *node, void *value, int (*cmp)(const void*, const void*))
{
	if (!node)
		return 0;
	
	if (cmp(node->data, value) > 0)
		return __get_key(node->left, value, cmp);
	else if (cmp(node->data, value) < 0)
		return __get_key(node->right, value, cmp);
	else
		return 1;

	return 0;
}

int
get_key(avl_tree_t *tree, void *value)
{
	return tree ? __get_key(tree->root, value, tree->cmp) : 0;
}

static avl_node_t *
__max_element(avl_node_t *node)
{
	return node->right ? __max_element(node->right) : node;
}

avl_node_t *
max_element(avl_tree_t *tree)
{
	return tree && tree->root ? __max_element(tree->root) : NULL;
}

/**
 * Deletes a value from an AVL subtree.
 * 
 * @node: The root of the current subtree.
 * @value: The data to be deleted from the AVL tree.
 * @cmp: Functia de comparare pentru datele din AVL.
 */
static void
__avl_delete(avl_node_t **node, void *value,
	int (*cmp)(const void*, const void*))
{
	if (!(*node))
		return;
	
	if (cmp((*node)->data, value) > 0)
	{
		__avl_delete(&(*node)->left, value, cmp);
	}
	else if (cmp((*node)->data, value) < 0)
	{
		__avl_delete(&(*node)->right, value, cmp);
	}
	else
	{
		if (!(*node)->right && !(*node)->left)
		{
			node_free(node);
			*node = NULL;
			return;
		}
		else if (!(*node)->right && (*node)->left)
		{
			avl_node_t *aux = *node;
			*node = (*node)->left;
			aux->left = NULL;
			node_free(&aux);
		}
		else if ((*node)->right && !(*node)->left)
		{
			avl_node_t *aux = *node;
			*node = (*node)->right;
			aux->right = NULL;
			node_free(&aux);
		}
		else
		{
			avl_node_t *max_node = __max_element((*node)->left);
			void *aux = (*node)->data;
			(*node)->data = max_node->data;
			max_node->data = aux;
			__avl_delete(&(*node)->left, max_node->data, cmp);
		}
	}
	(*node)->height = 1 + __max(__height((*node)->left), __height((*node)->right));
	__avl_fix(node);
}

void
avl_delete(avl_tree_t *tree, void *value)
{
	if (tree)
		__avl_delete(&tree->root, value, tree->cmp);
}

void
preorder_traversal(avl_node_t *node)
{
	if (!node)
		return;

	printf("%d ", *(int*)node->data);
	preorder_traversal(node->left);
	preorder_traversal(node->right);
}
