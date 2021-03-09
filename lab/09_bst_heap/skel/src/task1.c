/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Test BST Implementation
 */

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

char to_lower(char c)
{
	if ('A' <= c && c <= 'Z')
		return c + 0x20;
	return c;
}

int bst_cmp_str_lexicographically(const char *key1, const char *key2)
{
	int rc, i, len;

	len = strlen(key1) < strlen(key2) ? strlen(key1) : strlen(key2);
	for (i = 0; i < len; ++i) {
		rc = to_lower(key1[i]) - to_lower(key2[i]);

		if (rc == 0)
			continue;
		return rc;
	}

	rc = to_lower(key1[i]) - to_lower(key2[i]);
	return rc;
}

void print_inorder(bst_node_t *x)
{
    if (!x)
        return;

    print_inorder(x->left);
    printf("%s\n", x->data);
    print_inorder(x->right);
}

int main(void)
{
    bst_tree_t *bst;
	int N, task;
	char str[BUFSIZ];

	scanf("%d\n", &N);

	bst = bst_tree_create(bst_cmp_str_lexicographically);

	while (N--) {
		scanf("%d", &task);
		memset(str, 0, BUFSIZ);

		switch (task) {
		case 1:
			scanf("%s", str);
			bst_tree_insert(bst, str);
			break;
		case 2:
			scanf("%s", str);
			bst_tree_remove(bst, str);
			break;
		case 3:
			print_inorder(bst->root);
			break;
		default:
			perror("Invalid task!");
		}
	}

	bst_tree_free(bst);

    return 0;
}
