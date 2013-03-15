
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include "fileReader.h" //for loading graph from file
#include "randomize.h" //for shuffling edges
#include "tools.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>


#define MIN(a,b) (((a)<(b))?(a):(b))

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int> > graphP;


/* if edge doesn't affect on graph planarity, then it will be added
 * otherwise it won't. Returns wheter failed or not to add an edge */


int tryToAddEdge(graphP * theGraph, int u, int v)
{
    add_edge(u, v, *theGraph);
    int result = boyer_myrvold_planarity_test(*theGraph);
    if(!result)
    {
        remove_edge(u, v, *theGraph);
    }
    
    return result;
}


/* trying to add as much edges as it can while preserving planarity.
 * Returns the number of edges which were unable to add */
int tryToEmbed(graphP * theGraph, int ** edgesList, int edgesCount)
{
    int i;
    int edgesFailedToEmbed = 0;

    for(i = 0; i < edgesCount; i++)
    {
        if(!tryToAddEdge(theGraph, edgesList[i][0], edgesList[i][1]))
        {
            edgesFailedToEmbed++;
        }
    }
    return edgesFailedToEmbed;
}



/* main 
 * graph is read from a given file as parameter */
int main(int argc, char *argv[])
{
    int i, minEdgesFailedToEmbed, edgesFailedToEmbed;

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name");
        exit(1);
    }
    
    //puts(argv[1]);
    int edgesCount, vertexCount;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount, &vertexCount);
    
    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }
    
    /* 
    graphP testGraph = gp_New();
    gp_InitGraph(testGraph, vertexCount);
   
    for(i = 0; i < edgesCount; i++)
    {
        gp_AddEdge(testGraph, edgesList[i][0], 0, edgesList[i][1], 0);
    }

    if (gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
    {
        printf("graph is planar\n");
        exit(0);
    }
    gp_Free(&testGraph);
    */

    graphP theGraph(vertexCount);

    clock_t begin, end;
    double time_spent;

    srand(time(NULL));
    begin = clock();    
    minEdgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount); //1 iteration
    
    for(i = 0; i < edgesCount; i++) //figure out how many iterations you need
    {
        theGraph = graphP(vertexCount);
        shuffleEdges(edgesList, edgesCount);
        edgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount);
        minEdgesFailedToEmbed = MIN(minEdgesFailedToEmbed, edgesFailedToEmbed);
    }
    
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);

    printf("Minimum count of edges which failed to embed - %d\n", 
            minEdgesFailedToEmbed);
    
    freeMem(edgesList, edgesCount); 
    return 0;
}

