#include <stdio.h>
#include <string.h>
#include "Stack.h"

int main()
{
    int count_p[3] = {0, 0, 0}, inp_size;
    stack_t *stack = st_create(sizeof(char));
    char par;
    scanf("%d\n", &inp_size);
    for (int i = 0; i < inp_size; i++)
    {
        scanf("%c", &par);
        st_push(stack, &par);
    }
    while (!st_is_empty(stack))
    {
        if (*(char*)st_peek(stack) == ')')
            count_p[0]++;
        else if (*(char*)st_peek(stack) == ']')
            count_p[1]++;
        else if (*(char*)st_peek(stack) == '}')
            count_p[2]++;
        else if (*(char*)st_peek(stack) == '(')
            count_p[0]--;
        else if (*(char*)st_peek(stack) == '[')
            count_p[1]--;
        else if (*(char*)st_peek(stack) == '{')
            count_p[2]--;
        st_pop(stack);
        if (count_p[0] < 0 || count_p[1] < 0 || count_p[2] < 0)
        {
            printf("Nu e corecta parantezarea\n");
            return 0;
        }
    }
    if (count_p[0] != 0 || count_p[1] != 0 || count_p[2] != 0)
    {
        printf("Nu e corecta parantezarea\n");
    }
    else
    {
        printf("Este corecta parantezarea\n");
    }
    st_free(stack);
    return 0;    
}
