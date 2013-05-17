
/* randimize.h implementation file */

#include "stdlib.h"
#include "randomize.h"
#include "time.h"


/* shuffle given edges list in random order */
void shuffleEdges(int ** edgesList, int edgesCount)
{
    int i, j;
    int tmp1, tmp2;

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


/* shuffle given vector of edges in random order */
void shuffleEdges(std::vector<std::pair<int, int> > * edgesList)
{
    int i, j;
    int tmp1, tmp2;
	const int edgesCount = edgesList->size();

    for(i = edgesCount - 1; i >= 0; i--)
    {
        j = rand() % edgesCount;
        tmp1 = edgesList->at(i).first;
        tmp2 = edgesList->at(i).second;
        edgesList->at(i).first = edgesList->at(j).first;
        edgesList->at(i).second = edgesList->at(j).second;
        edgesList->at(j).first = tmp1;
        edgesList->at(j).second = tmp2;
    }
}
