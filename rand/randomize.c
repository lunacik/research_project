
/* randimize.h implementation file */

#include "stdlib.h"

/* shuffle given edges list in random order */
void shuffleEdges(int ** edgesList, int edgesCount)
{
    int i, j;
    int tmp1, tmp2;

    srand(time(NULL));
    for(i = edgesCount - 1; i >= 0; i--)
    {
        j = rand() % edgesCount;
        tmp1 = edgesList[i][0];
        tmp2 = edgesList[i][1];
        edgesList[i][0] = edgesList[j][0];
        edgesList[i][1] = edgesList[j][1];
        edgesList[j][0] = tmp1;
        edgesList[j][1] = tmp2;
    }
}

