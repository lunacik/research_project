
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <time.h>
#include "graph.h" //from planarity project
#include "fileReader.h" //for loading graph from file
#include "randomize.h" //for shuffling edges
#include "tools.h"

//#define SPEED_MACROS
//#define NONPLANAR NONEMBEDDABLE
#define MAXINT 2147483647


/* if edge doesn't affect on graph planarity, then it will be added
 * otherwise it won't. Returns wheter failed or not to add an edge */
int tryToAddEdge(graphP theGraph, int u, int v)
{
    graphP testGraph = gp_DupGraph(theGraph);
    gp_AddEdge(testGraph, u, 0, v, 0);
    int result = gp_Embed(testGraph, EMBEDFLAGS_PLANAR);
    
    if(result != NONPLANAR)
    {
        gp_AddEdge(theGraph, u, 0, v, 0);
    }
    gp_Free(&testGraph);
    return result;
}


/* trying to add as much edges as it can while preserving planarity.
 * Returns the number of edges which were unable to add */
int tryToEmbed(graphP theGraph, int ** edgesList, int edgesCount, int * edgesIndexes)
{
    int i;
    int edgesFailedToEmbed = 0;

    for(i = 0; i < edgesCount; i++)
    {
        if(tryToAddEdge(theGraph, edgesList[i][0], edgesList[i][1]) == NONPLANAR)
        {
            edgesIndexes[edgesFailedToEmbed] = i;
            edgesFailedToEmbed++;
        }
    }
    return edgesFailedToEmbed;
}



/* main 
 * graph is read from a given file as parameter */
int main(int argc, char *argv[])
{
    graphP theGraph;
    int i, j, index, minEdgesFailedToEmbed = MAXINT, edgesFailedToEmbed;

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file name");
        exit(1);
    }
    
    int edgesCount, vertexCount;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount, &vertexCount);
    
    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }
    
    
    graphP testGraph = gp_New();
    gp_InitGraph(testGraph, vertexCount + 1 + 1);
   
    for(i = 0; i < edgesCount; i++)
    {
        gp_AddEdge(testGraph, edgesList[i][0], 0, edgesList[i][1], 0);
        //printf("%d %d %d\n", i, edgesList[i][0], edgesList[i][1]);
    }

    testGraph = planarize_two_edges(testGraph, 3, 0, 4, 11, 2, 5);
    
    if (gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
    {
        printf("graph is planar\n");
        exit(0);
    }
    gp_Free(&testGraph);
  
    /*

    clock_t begin, end;
    double time_spent;

    int ** edges = malloc(edgesCount * sizeof(int*));
    int * edgesIndexes = malloc(edgesCount * sizeof(int));
    for(i = 0; i < edgesCount; i++)
    {
        edges[i] = malloc(2 * sizeof(int));
    }
    srand(time(NULL));
    begin = clock(); 
    
    for(i = 0; i < edgesCount; i++) //figure out how many iterations you need
    {
        theGraph = gp_New();
        gp_InitGraph(theGraph, vertexCount);
        shuffleEdges(edgesList, edgesCount);
        edgesFailedToEmbed = tryToEmbed(theGraph, edgesList, edgesCount, edgesIndexes);
        
        if(minEdgesFailedToEmbed > edgesFailedToEmbed)
        {
            minEdgesFailedToEmbed = edgesFailedToEmbed;
            
            for(j = 0; j < minEdgesFailedToEmbed; j++)
            {
                index = edgesIndexes[j];
                edges[j][0] = edgesList[index][0];
                edges[j][1] = edgesList[index][1];
            }
        }
        
        gp_Free(&theGraph);
    }
    end = clock();
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);
  
    char * a = "ABCDEFG"; 
    for(i = 0; i < minEdgesFailedToEmbed; i++)
    {
        printf("%c  %c\n", a[edges[i][0]], a[edges[i][1]]);
    }

    for(i = 0; i < edgesCount; i++)
    {
       free(edges[i]); 
    }
    free(edges);

    printf("count of edges which failed to embed - %d\n", 
            minEdgesFailedToEmbed);

    free(edgesIndexes); 
    freeMem(edgesList, edgesCount); 

    */

    return 0;
}

