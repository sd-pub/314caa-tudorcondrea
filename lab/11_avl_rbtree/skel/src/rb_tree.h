/* Laborator 11 SD - AVL / Red-Black
 * Authors:
 *
 * Andrei Topala - topala.andrei@gmail.com
 * Dorin Geman  - doringeman@gmail.com
 * Teodor Dutu - teodor.dutu@gmail.com
 *
 * SD, 2021
 */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

enum COLOR {
	RED = 0,
	BLACK
};

/**
 * The Red-Black node struct definition
 */
typedef struct rb_node_t rb_node_t;
struct rb_node_t {
	/* parent - RB_NODE_NULL for root */
	rb_node_t   *parent;
	/* left child - smaller key */
	rb_node_t   *left;
	/* right child - bigger key */
	rb_node_t   *right;

	/* the sorting is based on key */
	void		*key;
	/* data contained by the node */
	void		*data;

	/* color of the node */
	enum COLOR	color;
};

/**
 * The Red-Black tree struct definition
 */
typedef struct rb_tree_t rb_tree_t;
struct rb_tree_t {
	/* root of the tree */
	rb_node_t	*root;

	/* key size */
	size_t 		key_size;

    /* data size */
    size_t 		data_size;

	/* function used for sorting the keys */
	int	(*cmp)(const void *key1, const void *key2);
};

/**
 * Creates a new tree with given key sorting function
 * @f: function used for sorting the key
 * @ksz: size in bytes of the key to be put in the node
 * @dsz: size in bytes of the data to be put in the node
 * @return: pointer the the newly created tree or NULL if malloc failed
 */
rb_tree_t *
rb_tree_create(int (*f) (const void *, const void *), size_t ksz, size_t dsz);

/**
 * Inserts a node in a tree
 * @rb_tree: the tree where the node is going to be inserted
 * @key: the key of the node to be inserted in the @rb_tree
 * @data: the data of the node to be inserted in the @rb_tree
 * @return: pointer the the newly inserated node or NULL if malloc fails
 */
rb_node_t *
rb_tree_insert(rb_tree_t *rb_tree, void *key, void *data);

/**
 * Gets the data associated with a certain key
 * @rb_tree: the tree where the key is searched
 * @key: the key for which the data is wanted
 * @return: the data mapped to the key or NULL if not found
 */
void *
rb_tree_find(rb_tree_t *rb_tree, void *key);

/**
 * Recursively frees the tree
 * @rb_tree: the tree to free
 * @f_key: the function used to free the key's content of a node
 * @f_data: the function used to free the data's content of a node
 */
void
rb_tree_free(rb_tree_t *rb_tree, void (*f_key)(void *), void (*f_data)(void *));

#endif  /* RB_TREE_H_ */
