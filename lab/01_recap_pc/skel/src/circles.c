#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct{
    int x, y, r;
}cerc;

int distsq(int x1, int y1, int x2, int y2)
{
    return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int main()
{
    int n = 0, count = 0, i, j;
    cerc * cercuri = malloc(n * sizeof(cerc));
    DIE(cercuri == NULL, "nu au putut fi retinute cercurile");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d%d%d", &cercuri[i].x, &cercuri[i].y, &cercuri[i].r);
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
                if (distsq(cercuri[i].x, cercuri[i].y, cercuri[j].x, cercuri[j].y) <= (cercuri[i].r + cercuri[j].r)*(cercuri[i].r + cercuri[j].r))
                    count++;
    free(cercuri);
    printf("%d\n", count);
    return 0;
}
