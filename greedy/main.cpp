
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

#define MAXINT 999999
using namespace boost;


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
            failedEdgesList[edgesFailedToEmbed++] = i;
        }
    }
    return edgesFailedToEmbed;
}


int tryToEmbed0(graphP * theGraph, int ** edgesList, int edgesCount)
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
    
    if (boyer_myrvold_planarity_test(testGraph))
    {
        printf("graph is planar\n");
        exit(0);
    }
    */
    graphP theGraph(vertexCount);
    typedef std::pair<int, int> edge;
    edge edgesFailedToEmbedList[edgesCount];

    int * failedToEmbedIndexes = (int*)malloc(edgesCount * sizeof(int));

    srand(time(NULL));
    minEdgesFailedToEmbed = MAXINT;
    
    for(i = 0; i < edgesCount; i++) //figure out how many iterations you need
    {
        theGraph = graphP(vertexCount);
        shuffleEdges(edgesList, edgesCount);
        edgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount, failedToEmbedIndexes);
        if(edgesFailedToEmbed < minEdgesFailedToEmbed)
        {
            for(j = 0; j < edgesFailedToEmbed; j++)
            {
                edgesFailedToEmbedList[j] = edge(edgesList[failedToEmbedIndexes[j]][0], 
                        edgesList[failedToEmbedIndexes[j]][1]);
            }
            minEdgesFailedToEmbed = edgesFailedToEmbed;
        }
    }
    
    printf("Minimum count of edges which failed to embed - %d\n", 
            minEdgesFailedToEmbed);
   
    for(i = 0; i < edgesCount; i++)
    {
        for(j = 0; j < minEdgesFailedToEmbed; j++)
        {
            if(edgesList[i][0] == edgesFailedToEmbedList[j].first &&
                    edgesList[i][1] == edgesFailedToEmbedList[j].second)
            {
                edgesList[i][0] = edgesList[--edgesCount][0];
                edgesList[i][1] = edgesList[edgesCount][1];
                break;
            }
        }
    }

    int cr = 0;

    for(j = 0; j < minEdgesFailedToEmbed; j++)
    {
        printf("%d %d\n", edgesFailedToEmbedList[j].first, edgesFailedToEmbedList[j].second);
        theGraph = graphP(vertexCount);
        int ** newEdgesList = (int**)malloc(edgesCount * sizeof(int*));
        int newEdgesCount = 0;
        add_edge(edgesFailedToEmbedList[j].first, edgesFailedToEmbedList[j].second, theGraph);
        for(i = 0; i < edgesCount; i++)
        {
           if(edgesList[i][0] == edgesFailedToEmbedList[j].first ||
                    edgesList[i][1] == edgesFailedToEmbedList[j].second ||
                    edgesList[i][0] == edgesFailedToEmbedList[j].second ||
                    edgesList[i][1] == edgesFailedToEmbedList[j].first)
            {
                add_edge(edgesList[i][0], edgesList[i][1], theGraph);
            }
            else
            {
                newEdgesList[newEdgesCount] = (int*)malloc(2 * sizeof(int));
                newEdgesList[newEdgesCount][0] = edgesList[i][0];
                newEdgesList[newEdgesCount++][1] = edgesList[i][1];
            }
        }
        
        graphP theGraphCopy = theGraph;

        int tmpCr = tryToEmbed0(&theGraph, newEdgesList, newEdgesCount);
        int failedToEmbed;

        for(i = 0; i < newEdgesCount - 1; i++)
        {
            theGraph = theGraphCopy;
            shuffleEdges(newEdgesList, newEdgesCount);
            failedToEmbed = tryToEmbed0(&theGraph, newEdgesList, newEdgesCount);
            if(failedToEmbed < tmpCr)
            {
                tmpCr = failedToEmbed;
            }
        }
        printf("%d tmpCr\n", tmpCr); 
        cr += tmpCr;
        
        freeMem(newEdgesList, newEdgesCount);
    }
    
    printf("Finaly the crossing number is - %d\n", cr); 
    freeMem(edgesList, edgesCount); 
    return 0;
}

