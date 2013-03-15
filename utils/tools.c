
/* tools.h implementation file */

#include "tools.h"
#include "stdlib.h"


graphP planarize_two_edges(graphP theGraph, int i1, int u1, int v1, int i2, int u2, int v2)
{
    graphP newGraph = gp_DupGraph(theGraph);
    //graphP newGraph = gp_New();
    //gp_InitGraph(newGraph, theGraph->N);
    //gp_CopyGraph(newGraph, theGraph);
    // newGraph->N = theGraph->N + 1;
    int DOUBLED_VERTEX_COUNT = theGraph->N * 2;   
    int arcPos1 = DOUBLED_VERTEX_COUNT + i1 * 2;
    int arcPos2 = DOUBLED_VERTEX_COUNT + i2 * 2;
    
    gp_HideEdge(newGraph, arcPos1);
    gp_HideEdge(newGraph, arcPos2);
    
    int newVertex = newGraph->N - 1;
    printf("%d\n", newVertex);
   
    gp_AddEdge(newGraph, u1, newVertex, 0, 0); 
    gp_AddEdge(newGraph, v1, newVertex, 0, 0);
    gp_AddEdge(newGraph, u2, newVertex, 0, 0);
    gp_AddEdge(newGraph, v2, newVertex, 0, 0);
    return newGraph;
}



/* freeing allocated memory for edges */
void freeMem(int ** edgesList, int edgesCount)
{
    int i;
    for(i = 0; i < edgesCount; i++)
    {
        free(edgesList[i]);
    }
    free(edgesList);
}
