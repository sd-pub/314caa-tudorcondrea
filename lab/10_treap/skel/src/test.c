#include <stdio.h>
#include "treap.h"

int
compar(void* value1, void* value2)
{

    int* a = (int*)value1;
    int* b = (int*)value2;
    if ((*a) > (*b)) {
        return 1;
    } else if ((*a) < (*b)) {
        return -1;
    }
    return 0;
}

void
inord(Node *node)
{
    if (!node)
        return;
    
    inord(node->left);
    printf("%d\n", *(int*)node->data);
    inord(node->right);
}

int main()
{
    Treap_tree* tree = treap_create((int (*)(void*, void*))(compar));
    int a = 6;
    treap_insert(&tree->root, &a, sizeof(int), compar);
    inord(tree->root);
    printf("\n");
    a = 4;
    treap_insert(&tree->root, &a, sizeof(int), compar);
    inord(tree->root);
    printf("\n");
    a = 2;
    treap_insert(&tree->root, &a, sizeof(int), compar);
    inord(tree->root);
    printf("\n");
    a = 5;
    treap_insert(&tree->root, &a, sizeof(int), compar);
    inord(tree->root);
    printf("\n");
    a = 10;
    treap_insert(&tree->root, &a, sizeof(int), compar);
    inord(tree->root);
    printf("%p %p %p\n", tree->root, tree->root->left, tree->root->right);
    return 0;
}