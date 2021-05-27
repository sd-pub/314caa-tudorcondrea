/* Laborator 11 SD - AVL / Red-Black
 * Authors:
 *
 * Andrei Topala - topala.andrei@gmail.com
 * Dorin Geman  - doringeman@gmail.com
 * Teodor Dutu - teodor.dutu@gmail.com
 *
 * Echipa SD, 2021
 */

#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "utils.h"

/**
 * Function that compares ints.
 * @return is similiar to that of strcmp.
 */
static int
cmp(const void* value1, const void* value2)
{

	int a = *(int*)value1; 
	int b = *(int*)value2;

	return (a < b ? -1 : (a == b) ? 0 : 1);
}

int
main(void)
{
	int task, no_inserts, no_deletes, no_finds, value, i;
	avl_tree_t *tree = avl_create(cmp);
	DIE(!tree, "failed to allocate tree");

	scanf("%d", &task);
	/* ------------- TASK 1 ------------- */
	if (task == 1)
		puts("------------- TASK 1 -------------");

	scanf("%d", &no_inserts);
	for (i = 0; i < no_inserts; ++i) {
		scanf("%d", &value);
		avl_insert(tree, &value, sizeof(value));

		/* Used for checker. */
		if (task == 1) {
			printf("Preoder: ");
			preorder_traversal(tree->root);
			printf("\n");
		}
	}

	if (task >= 2) {
		/* ------------- TASK 2 ------------- */
		if (task == 2)
			puts("------------- TASK 2 -------------");

		scanf("%d", &no_finds);
		for (i = 0; i < no_finds; ++i) {
			scanf("%d", &value);

			if (task == 3)
				continue;   

			if (get_key(tree, &value))
				printf("%d is in AVL.\n", value);
			else
				printf("%d is NOT in AVL.\n", value);
		}
	}

	/* ------------- TASK 4 ------------- */
	if (task == 3) {
		puts("------------- TASK 3 -------------");

		scanf("%d", &no_deletes);
		for (i = 0; i < no_deletes; ++i) {
			scanf("%d", &value);
			avl_delete(tree, &value);

			/* Used for checker. */
			printf("Preoder: ");
			preorder_traversal(tree->root);
			printf("\n");
		}
	}

	return 0;
}
