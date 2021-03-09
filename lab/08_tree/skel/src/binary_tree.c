/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #1 - Binary Tree implementation
 */

#include "binary_tree.h"
#include "queue.h"
#include "utils.h"

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 */
static b_node_t *__b_node_create(int data)
{
	b_node_t *b_node;

	b_node = malloc(sizeof(b_node_t));
	DIE(b_node == NULL, "b_node malloc");

	b_node->left = b_node->right = NULL;

	b_node->data = malloc(sizeof(int));
	DIE(b_node->data == NULL, "b_node->data malloc");
	*b_node->data = data;

	return b_node;
}

b_tree_t *b_tree_create()
{
	/* TODO */
	return NULL;
}

void b_tree_insert(b_tree_t *b_tree, int data)
{
	Queue *q;
	b_node_t *b_node, *b_node_tmp;

	b_node = __b_node_create(data);

	if (!b_tree->root) {
		b_tree->root = b_node;
		return;
	}

	q = malloc(sizeof(Queue));
	init_q(q);

	/* TODO */

	purge_q(q);
	free(q);
}

static void __b_tree_print_preorder(b_node_t *b_node)
{
	if (!b_node)
		return;

   /* TODO */
}

void b_tree_print_preorder(b_tree_t *b_tree)
{
	__b_tree_print_preorder(b_tree->root);
	printf("\n");
}

static void __b_tree_print_inorder(b_node_t *b_node)
{
	if (!b_node)
		return;

	/* TODO */
}

void b_tree_print_inorder(b_tree_t *b_tree)
{
	__b_tree_print_inorder(b_tree->root);
	printf("\n");
}

static void __b_tree_print_postorder(b_node_t *b_node)
{
	if (!b_node)
		return;

	/* TODO */
}

void b_tree_print_postorder(b_tree_t *b_tree)
{
	__b_tree_print_postorder(b_tree->root);
	printf("\n");
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 */
static void __b_tree_free(b_node_t *b_node)
{
	if (!b_node)
		return;

	/* TODO */
}

void b_tree_free(b_tree_t *b_tree)
{
	__b_tree_free(b_tree->root);
	free(b_tree);
}
