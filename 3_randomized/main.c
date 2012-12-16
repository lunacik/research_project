
/* In this approach we are to remove random edges. If graph becomes planar,
 * we try to return as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <time.h>
#include "graph.h" //from planarity project
#include "fileReader.h" //for loading graph from file
#include "randomize.h" //for shuffling edges



/* trying to restore as much edges as we can */
/* FIXME maybe useless and currently not working  */
int restoreEdges(int * randomList, int listSize, graphP * theGraph, int DEC)
{
    int i, newSize, arcPos;
    randomList = getRandomEdgesFromList(randomList, listSize, &newSize);
    graphP testGraph;
    for(i = 0; i < newSize; i++)
    {
        arcPos = DEC + randomList[i] * 2;
        gp_RestoreEdge(*theGraph, arcPos);
        
        testGraph = gp_DupGraph(*theGraph);
        if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR == NONPLANAR))
        {
            return i;
        }
        gp_Free(&testGraph);
    }
    return restoreEdges(randomList, newSize, theGraph, DEC);
}



/* removing some random edges from graph and testing if it becomes planar */
int removeRandomEdges(graphP * theGraph, int edgesCount)
{
    int i, listSize, arcPos;
    int * randomList;
    const int DOUBLED_EDGES_COUNT = edgesCount * 2;
    
    randomList = getRandomEdges(&listSize, edgesCount);
    
    for(i = 0; i < listSize; i++)
    {
        arcPos = DOUBLED_EDGES_COUNT + randomList[i] * 2;
        gp_HideEdge(*theGraph, arcPos);
    }
    graphP testGraph = gp_DupGraph(*theGraph);
    
    for(i = 0; i < listSize; i++)
    {
        arcPos = DOUBLED_EDGES_COUNT + randomList[i] * 2;
        gp_RestoreEdge(*theGraph, arcPos);
    }   
    
    free(randomList);
    if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR) == NONPLANAR)
    {
        gp_Free(&testGraph);
        return edgesCount; //to be not treated like minimum
    }
    else
    {
        gp_Free(&testGraph);
        return listSize;
        //return restoreEdges(randomList, listSize, theGraph, DOUBLED_EDGES_COUNT);
    }

}



/* main 
 * graph is read from a given file as parameter */
int main(int argc, char * argv[])
{
    graphP theGraph = gp_New();

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name");
        exit(1);
    }
    
    int edgesCount;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount);
    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }

    gp_InitGraph(theGraph, edgesCount);
    
    int i;
    for(i = 0; i < edgesCount; i++)
    {
        gp_AddEdge(theGraph, edgesList[i][0], 0, edgesList[i][1], 0);
    }
    
    graphP testGraph = gp_DupGraph(theGraph);
    if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
    {
        printf("graph is planar\n");
        exit(0);
    }
    gp_Free(&testGraph);


    clock_t begin, end;
    double time_spent;

    begin = clock();    
    //logic goes here
     
    srand(time(NULL));
    int minEdgesFailedToEmbed = removeRandomEdges(&theGraph, edgesCount); //1 iteration
    int tmp, j;
    for(i = 0; i < 1000; i++) // figure out how many iterations
    {
        tmp = removeRandomEdges(&theGraph, edgesCount);
        minEdgesFailedToEmbed = MIN(tmp, minEdgesFailedToEmbed);
    }
    end = clock();

    printf("Minimum count of edges which failed to embed - %d\n", 
            minEdgesFailedToEmbed);

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);
     
    gp_Free(&theGraph);
    freeMem(edgesList, edgesCount); 
    
    return 0;
}

