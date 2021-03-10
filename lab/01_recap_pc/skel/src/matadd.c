#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int main()
{
    int **mat, n, m;
    scanf("%d%d", &n, &m);
    mat = malloc(sizeof(int *) * n);
    DIE(mat == NULL, "nu a putut fi alocata matricea\n");
    int i, j;
    for(i = 0; i < n; i++)
    {
        mat[i] = malloc(sizeof(int) * m);
        DIE(mat[i] == NULL, "nu a putut fi alocata matricea\n");
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &mat[i][j]);
    int nr, sum;
    sum = 0;
    for(i = 0; i < n; i++)
    {
        nr = 0;
        for (j = 0; j < m; j++)
        {
            nr *= 10;
            nr += mat[i][j];
        }
        sum += nr;
    }
    for(i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
    printf("%d\n", sum);
    return 0;
}
