
/* tools.h implementation file */

#include "tools.h"
#include "stdlib.h"


void planarize_two_edges(graphD * theGraph, int u1, int v1, int u2, int v2, int newVertex)
{
	remove_edge(u1, v1, *theGraph);
    //remove_edge(u2, v2, *theGraph);

    add_edge(u1, newVertex, *theGraph); 
    add_edge(v1, newVertex, *theGraph); 
    add_edge(u2, newVertex, *theGraph);
    add_edge(v2, newVertex, *theGraph);
}

void planarize_one_edge(graphD * theGraph, int u1, int v1, int u2, int newVertex)
{
	remove_edge(u1, v1, *theGraph);

    add_edge(u1, newVertex, *theGraph);
    add_edge(v1, newVertex, *theGraph);
    add_edge(u2, newVertex, *theGraph);
}

/* freeing allocated memory for edges */
void freeEdgesList(int ** edgesList, int edgesCount)
{
    for(int i = 0; i < edgesCount; i++)
    {
        free(edgesList[i]);
    }
    free(edgesList);
}
