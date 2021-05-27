/* Laborator 11 SD - AVL / Red-Black
 * Authors:
 *
 * Andrei Topala - topala.andrei@gmail.com
 * Dorin Geman  - doringeman@gmail.com
 * Teodor Dutu - teodor.dutu@gmail.com
 *
 * SD, 2021
 */

#include "rb_tree.h"

/**
 * Creates a new Red-Black node
 */
static rb_node_t *
rb_node_create(void *key, void *data, size_t key_size, size_t data_size)
{
	rb_node_t *rb_node;

	rb_node = (rb_node_t *) malloc(sizeof(rb_node_t));
	if (rb_node == NULL)
		return NULL;

	rb_node->parent = rb_node->left = rb_node->right = NULL;

	rb_node->key = malloc(key_size);
	if (rb_node->key == NULL)
		return NULL;
	memcpy(rb_node->key, key, key_size);

	rb_node->data = malloc(data_size);
	if (rb_node->data == NULL)
		return NULL;
	memcpy(rb_node->data, data, data_size);

	rb_node->color	= RED;

	return rb_node;
}

rb_tree_t *
rb_tree_create(int (*f) (const void *, const void *), size_t ksz, size_t dsz)
{
	rb_tree_t *rb_tree;

	rb_tree = (rb_tree_t *) malloc(sizeof(rb_tree_t));
	if (rb_tree == NULL)
		return NULL;

	rb_tree->cmp = f;
	rb_tree->data_size = dsz;
	rb_tree->key_size = ksz;
	rb_tree->root = NULL;

	return rb_tree;
}

/**
 * Swaps the color of node_a and node_b
 */
static void
__swap_color(rb_node_t *node_a, rb_node_t *node_b)
{
	enum COLOR color = node_a->color;
	node_a->color = node_b->color;
	node_b->color = color;
}

/**
 * Rotates the tree to the left
 * @rb_tree: the tree which is going to be rotated to the left
 * @rb_node: the node which causes the need of rotation
 */
static void
__rb_tree_rotate_left(rb_tree_t *rb_tree, rb_node_t *rb_node)
{
	rb_node_t *right_child = rb_node->right;

	rb_node->right = right_child->left;

	if (rb_node->right != NULL)
		rb_node->right->parent = rb_node;

	right_child->parent = rb_node->parent;

	if (rb_node->parent == NULL)
		rb_tree->root = right_child;
	else if (rb_node == rb_node->parent->left)
		rb_node->parent->left = right_child;
	else
		rb_node->parent->right = right_child;

	right_child->left = rb_node;
	rb_node->parent = right_child;
}

/**
 * Rotates the tree to the right
 * @rb_tree: the tree which is going to be rotated to the right
 * @rb_node: the node which causes the need of rotation
 */
static void
__rb_tree_rotate_right(rb_tree_t *rb_tree, rb_node_t *rb_node)
{
	rb_node_t *left_child = rb_node->left;
	rb_node->left = left_child->right;

	if (rb_node->left)
		rb_node->left->parent = rb_node;
	left_child->parent = rb_node->parent;

	if (!rb_node->parent)
		rb_tree->root = left_child;
	else if (rb_node == rb_node->parent->right)
		rb_node->parent->right = left_child;
	else
		rb_node->parent->left = left_child;

	left_child->right = rb_node;
	rb_node->parent = left_child;
}

/**
 * Checks if the tree needs to be rotated
 * @return: 1 if it needs a rotation or 0 if it does not
 */
static int
__check_violation(rb_tree_t *rb_tree, rb_node_t *rb_node)
{
	return (
			(rb_node != rb_tree->root)	&&
			(rb_node->color != BLACK)	&&
			(rb_node->parent->color == RED)
	);
}

/**
 * Checks if the tree needs to be rotated after the insertion of a new node
 * @rb_tree: the tree containing the node
 * @rb_node: the newly inserted node
 */
static void
__rb_tree_insert_fix(rb_tree_t *rb_tree, rb_node_t *rb_node)
{
	rb_node_t *grand_parent, *parent, *uncle;

	while (__check_violation(rb_tree, rb_node)) {

		parent = rb_node->parent;
		grand_parent = rb_node->parent->parent;

		if (parent == grand_parent->left) {
			uncle = grand_parent->right;

			if ((uncle != NULL) && (uncle->color == RED)) {
				grand_parent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				rb_node = grand_parent;
			} else {
				if (rb_node == parent->right) {
					__rb_tree_rotate_left(rb_tree, parent);
					rb_node = parent;
					parent = rb_node->parent;
				}

				__rb_tree_rotate_right(rb_tree, grand_parent);
				__swap_color(parent, grand_parent);
				rb_node = parent;
			}

		} else {
			uncle = grand_parent->left;

			if(!uncle && uncle->color == RED)
			{
				grand_parent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				rb_node = grand_parent;
			}
			else
			{
				if (rb_node == parent->left)
				{
					__rb_tree_rotate_right(rb_tree, parent);
					rb_node = parent;
					parent = rb_node->parent;
				}
				__rb_tree_rotate_left(rb_tree, grand_parent);
				__swap_color(parent, grand_parent);
				rb_node = parent;
			}
			
		}
	}

	rb_tree->root->color = BLACK;
}

rb_node_t *
rb_tree_insert(rb_tree_t *rb_tree, void *key, void *data)
{
	int rc;
	rb_node_t *root		= rb_tree->root;
	rb_node_t *parent	= NULL;
	rb_node_t *node;

	node = rb_node_create(key, data, rb_tree->key_size, rb_tree->data_size);
	if (node == NULL)
		return NULL;

	while (root != NULL) {
		rc = rb_tree->cmp(node->key, root->key);
		if (rc == 0)
			return root;

		parent = root;

		if (rc < 0)
			root = root->left;
		else
			root = root->right;
	}

	node->parent	= parent;
	node->left		= NULL;
	node->right		= NULL;

	if (parent != NULL) {
		if (rc < 0)
			parent->left = node;
		else
			parent->right = node;
	} else {
		rb_tree->root = node;
	}

	__rb_tree_insert_fix(rb_tree, node);
	return node;
}

void *
rb_tree_find(rb_tree_t *rb_tree, void *key)
{
	int rc;
	rb_node_t *node = rb_tree->root;

	while (node != NULL) {
		rc = rb_tree->cmp(key, node->key);

		if (rc == 0)
			return node->data;

		if (rc < 0)
			node = node->left;
		else
			node = node->right;
	}

	return NULL;
}

static void
__rb_tree_free(rb_node_t *root, void (*f_key)(void *), void (*f_data)(void *))
{
	if (root == NULL)
		return;

	/* TODO */

	if (f_key != NULL)
		f_key(root->key);
	free(root->key);

	if (f_data != NULL)
		f_data(root->data);
	free(root->data);

	if (root->left)
	{
		__rb_tree_free(root->left, f_key, f_data);
		root->left = NULL;
	}
	if (root->right)
	{
		__rb_tree_free(root->right, f_key, f_data);
		root->right = NULL;
	}
	
	free(root);
}

void
rb_tree_free(rb_tree_t *rb_tree, void (*f_key)(void *), void (*f_data)(void *))
{
	__rb_tree_free(rb_tree->root, f_key, f_data);
}
