
/* randimize.h implementation file */

#include "stdlib.h"
#include "randomize.h"
#include "time.h"

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



/* generating list random of indexes of random size */
int * getRandomEdges(int * listSize, int edgesCount)
{
    srand(time(NULL));
    *listSize = rand() % edgesCount; //maybe some range will be more efficient
    int i, j, tmp, unique = 1;
    int * list = malloc(*listSize * sizeof(int));
    for(i = 0; i < *listSize; i++)
    {
        tmp = rand() % edgesCount;
        for(j = 0; j < i; j++)
        {
            if(list[j] == tmp)
            {
                unique = 0;
                break;
            }
        }
        if(unique)
        {
            list[i] = tmp;
        }
        else
        {
            unique = 1;
            i--;
        }
    }
    return list;
}


/* method to return random number of random edges from list */
int * getRandomEdgesFromList(int * list, int listSize, int * newListSize)
{
    srand(time(NULL));
    *newListSize = rand() % listSize; //size can be same as initial list or zero - flaw or pros?
    int * newList = malloc(*newListSize * sizeof(int));
    int i, j, tmp, unique = 1;
    for(i = 0; i < *newListSize; i++)
    {
        tmp = list[rand() % listSize];
        for(j = 0; j < i; j++)
        {
            if(newList[j] == tmp)
            {
                unique = 0;
                break;
            }
        }
        if(unique)
        {
            newList[i] = tmp;
        }
        else
        {
            unique = 1;
            i--;
        }
    }
    return newList;
}






