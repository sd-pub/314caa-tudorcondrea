#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 64

int
main()
{
    linked_list_t* linkedList;
    int is_int = 0;
    int is_string = 0;
    while (1) {
        char command[16], added_elem[64], *end_ptr;
        long nr, pos;
        scanf("%s", command);
        if (strcmp(command, "create_str") == 0) {
            linkedList = ll_create(MAX_STRING_SIZE);
            is_string = 1;
        }
        if (strcmp(command, "create_int") == 0) {
            linkedList = ll_create(sizeof(int));
            is_int = 1;
        }
        if (strcmp(command, "add") == 0) {
            scanf("%ld", &pos);
            scanf("%s", added_elem);
            nr = strtol(added_elem, &end_ptr, 10);
            if (nr != 0) {
                ll_add_nth_node(linkedList, pos, &nr);
            } else {
                ll_add_nth_node(linkedList, pos, end_ptr);
            }
        }
        if (strcmp(command, "remove") == 0) {
            scanf("%ld", &pos);
            ll_remove_nth_node(linkedList, pos);
        }
        if (strcmp(command, "print") == 0) {
            if (is_int == 1) {
                ll_print_int(linkedList);
            }
            if (is_string == 1) {
                ll_print_string(linkedList);
            }
        }
        if (strcmp(command, "free") == 0) {
            ll_free(&linkedList);
            break;
        }
    }
    return 0;
}
