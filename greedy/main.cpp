
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include "graph.h"
#include "fileReader.h" //for loading graph from file
#include "randomize.h" //for shuffling edges
#include "tools.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <tuple>

#define MIN(a,b) (((a)<(b))?(a):(b))


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
int tryToEmbed(graphP * theGraph, int ** edgesList, int edgesCount, int * failedEdgesList)
{
    int i;
    int edgesFailedToEmbed = 0;

    for(i = 0; i < edgesCount; i++)
    {
        if(!tryToAddEdge(theGraph, edgesList[i][0], edgesList[i][1]))
        {
            edgesFailedToEmbed++;
            failedEdgesList[edgesFailedToEmbed] = i;
        }
    }
    return edgesFailedToEmbed;
}



/* main 
 * graph is read from a given file as parameter */
int main(int argc, char *argv[])
{
    int i, j, minEdgesFailedToEmbed, edgesFailedToEmbed;

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name");
        exit(1);
    }
    
    int edgesCount, vertexCount;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount, &vertexCount);
    
    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }
    /* 
    graphP testGraph(0);
   
    for(i = 0; i < edgesCount; i++)
    {
        add_edge(edgesList[i][0], edgesList[i][1], testGraph);
    }
    
    planarize_two_edges(&testGraph, 0, 5, 1, 2, 7);
    planarize_two_edges(&testGraph, 0, 3, 1, 4, 8);
    planarize_two_edges(&testGraph, 0, 6, 1, 5, 9);
    planarize_two_edges(&testGraph, 1, 3, 0, 2, 10);
    planarize_two_edges(&testGraph, 1, 6, 0, 4, 11);
    planarize_two_edges(&testGraph, 3, 4, 0, 1, 12);
    
    planarize_two_edges(&testGraph, 3, 4, 0, 1, 12);
    planarize_two_edges(&testGraph, 3, 4, 0, 1, 12);
    planarize_two_edges(&testGraph, 3, 4, 0, 1, 12);
    
    if (boyer_myrvold_planarity_test(testGraph))
    {
        printf("graph is planar\n");
        exit(0);
    }
    */
    graphP theGraph(vertexCount);
    
    typedef std::pair<int, int> edge;

    edge e1(1, 2);
    edge e2(1, 2);
    
    edge edgesFailedToEmbedList[edgesCount];

    int * failedToEmbedIndexes = (int*)malloc(edgesCount * sizeof(int));

    clock_t begin, end;
    double time_spent;

    srand(time(NULL));
    begin = clock();    
    minEdgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount, failedToEmbedIndexes);
    
    for(i = 0; i < edgesCount - 1; i++) //figure out how many iterations you need
    {
        theGraph = graphP(vertexCount);
        shuffleEdges(edgesList, edgesCount);
        edgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount, failedToEmbedIndexes);
        for(j = 0; j < edgesFailedToEmbed; j++)
        {
            edgesFailedToEmbedList[j] = edge(edgesList[failedToEmbedIndexes[j]][0], 
                    edgesList[failedToEmbedIndexes[j]][1]);
        }
        minEdgesFailedToEmbed = MIN(minEdgesFailedToEmbed, edgesFailedToEmbed);
    }
    
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);

    printf("Minimum count of edges which failed to embed - %d\n", 
            minEdgesFailedToEmbed);
   
    for(j = 0; j < minEdgesFailedToEmbed; j++)
    {
        //printf("%d %d\n", edgesFailedToEmbedList[j].first, edgesFailedToEmbedList[j].second);
    }

    freeMem(edgesList, edgesCount); 
    return 0;
}

