
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <time.h>
#include "graph.h" //from planarity project
#include "fileReader.h" //for file processing
#include "randomize.h" //for shuffling edges


/* if edge doesn't affect on graph planarity, then it will be added
 * otherwise it won't. Returns wheter failed or not to add an edge */
int tryToAddEdge(graphP * theGraph, int u, int v)
{
    graphP testGraph = gp_DupGraph(*theGraph);
    gp_AddEdge(testGraph, u, 0, v, 0);
    int result = gp_Embed(testGraph, EMBEDFLAGS_PLANAR);
    if(result != NONPLANAR)
    {
        gp_AddEdge(*theGraph, u, 0, v, 0);
    }
    gp_Free(&testGraph);
    return result;
}


/* trying to add as much edges as it can while preserving planarity.
 * Returns the number of edges which were unable to add */
int tryToEmbed(graphP * theGraph, int edgesList[][2], int edgesCount)
{
    int i;
    int edgesFailedToEmbed = 0;

    for(i = 0; i < edgesCount; i++)
    {
        if(tryToAddEdge(theGraph, edgesList[i][0], edgesList[i][1]) == NONPLANAR)
        {
            edgesFailedToEmbed++;
        }
    }
    return edgesFailedToEmbed;
}


/* main 
 * graph is read from a given file as parameter*/
int main(int argc, char *argv[])
{
    graphP theGraph = gp_New();
    int i, minEdgesFailedToEmbed, edgesFailedToEmbed;

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name");
        exit(1);
    }
    
    const int edgesCount = getEdgesCount(argv[1]);

    int edgesList[edgesCount][2];

    if(!readGraphFromFile(argv[1], edgesList))
    {
        printf("reading from file failed\n");
        exit(1);
    }

    gp_InitGraph(theGraph, edgesCount);
    
    minEdgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount); //1 iteration
    gp_Free(&theGraph);

    for(i = 0; i < 100; i++) //figure out how many iterations you need
    {
        theGraph = gp_New();
        gp_InitGraph(theGraph, edgesCount);
        shuffleEdges(edgesList, edgesCount);
        edgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount);
        minEdgesFailedToEmbed = MIN(minEdgesFailedToEmbed, edgesFailedToEmbed);
        gp_Free(&theGraph);
    } 

    printf("Minimum count of edges which failed to embed - %d\n", 
            minEdgesFailedToEmbed);
    
    return 0;
}

