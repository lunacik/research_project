
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include "greedy.h"
#include "randomize.h" //for shuffling edges
#include "tools.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

#define MAXINT 9999999

using namespace boost;


/* if edge doesn't affect on graph planarity, then it will be added
 * otherwise it won't. Returns wheter failed or not to add an edge */
int tryToAddEdge(graphD * theGraph, int u, int v)
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
int tryToEmbed(graphD * theGraph, int ** edgesList,
		int edgesCount, int * failedEdgesList)
{
    int edgesFailedToEmbed = 0;

    for(int i = 0; i < edgesCount; i++)
    {
        if(!tryToAddEdge(theGraph, edgesList[i][0], edgesList[i][1]))
        {
            failedEdgesList[edgesFailedToEmbed++] = i;
        }
    }
    return edgesFailedToEmbed;
}


/*Selecting the smallest edges failed to embed count*/
int getEFTEC(int ** edgesList, int edgesCount, int ** edgesFailedToEmbedList,
		std::vector<std::pair<int, int> > * edgesSucceedToEmbed, int iterations)
{
	int edgesFailedToEmbed, minEdgesFailedToEmbed = MAXINT;
    int * failedToEmbedIndexes = (int*)malloc(edgesCount * sizeof(int));

    srand(time(NULL));

    for(int i = 0; i < iterations; i++) //figure out how many iterations you need
    {
    	graphD theGraph = graphD(0);
        shuffleEdges(edgesList, edgesCount);
        edgesFailedToEmbed = tryToEmbed(&theGraph, edgesList, edgesCount, failedToEmbedIndexes);
        if(edgesFailedToEmbed < minEdgesFailedToEmbed)
        {
            for(int j = 0; j < edgesFailedToEmbed; j++)
            {
                edgesFailedToEmbedList[j][0] = edgesList[failedToEmbedIndexes[j]][0];
                edgesFailedToEmbedList[j][1] = edgesList[failedToEmbedIndexes[j]][1];
            }

        	edgesSucceedToEmbed->clear();

            for(int j = 0; j < edgesCount; j++)
            {
            	bool found = false;
            	for(int k = 0; k < edgesFailedToEmbed; k++)
            	{
            		if(failedToEmbedIndexes[k] == j)
            		{
            			found = true;
            			break;
            		}
            	}
        		if(!found)
        		{
            		edgesSucceedToEmbed->push_back(std::pair<int, int>(edgesList[j][0], edgesList[j][1]));
        		}
            }

            minEdgesFailedToEmbed = edgesFailedToEmbed;
        }
    }

    free(failedToEmbedIndexes);
    return minEdgesFailedToEmbed;
}
