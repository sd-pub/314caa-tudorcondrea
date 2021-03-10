#include <stdlib.h>
#include <stdio.h>

int main()
{
    int **mat, n, m;
    scanf("%d%d", &n, &m);
    mat = (int **)malloc(sizeof(int *) * n);
    int i, j;
    for(i = 0; i < n; i++)
        mat[i] = (int *)malloc(sizeof(int) * m);
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