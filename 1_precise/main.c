
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cahideEdgesAndTryToEmbed graph to be nonplanar */

#include <stdlib.h> //standard C definitions
#include <time.h> //for time recording
#include "graph.h" //from planarity project
#include "fileReader.h" //for loading graph from file

graphP testGraph;
int DOUBLED_EDGES_COUNT;


/* hiding edges edges and checking if graph becomes planar*/
int hideEdgesAndTryToEmbed(stackP bitset, graphP * theGraph)
{
    int j = 0, arcPos;
    int i = bitset->S[j++];
 
    while(i != -1) //hiding edges
    {
        arcPos = DOUBLED_EDGES_COUNT + i * 2;
        gp_HideEdge(*theGraph, arcPos);
        i = bitset->S[j++];
    }
    gp_CopyGraph(testGraph, *theGraph);
    j = 0;
    i = bitset->S[j++];
    while(i != -1) //restoring edges
    {
        arcPos = DOUBLED_EDGES_COUNT + i * 2;
        gp_RestoreEdge(*theGraph, arcPos);
        i = bitset->S[j++];
    }    
    //checking if graph is planar
    if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
    {
        //gp_ReinitializeGraph(testGraph);
        return 1;
    }
    else
    {
        //gp_ReinitializeGraph(testGraph);
        return 0;
    }
}


/* generating combinations of pairs and calling hide edges routine */
int generateBitsetAndHideEdges(int length, int start, stackP bitset, graphP * theGraph)
{
    if(!length)
    {
        return hideEdgesAndTryToEmbed(bitset, theGraph);
    }
    int i, retVal = 0;
    for(i = start; i < (*theGraph)->M; i++)
    {
        sp_Push(bitset, i);
        if((retVal = generateBitsetAndHideEdges(length - 1, i + 1, bitset, theGraph) != 0))
        {
            return retVal; //success
        }
        bitset->S[--bitset->Top];
    }

    return 0; //failed
}


/* preparint bitset and 
 * calling generateBitsetAndHideEdges routine from 1 to n times */
int getMinEdgesFailedToEmbed(graphP * theGraph)
{
    stackP st;
    st = sp_New((*theGraph)->M);
    int i;
    for(i = 0; i < (*theGraph)->M; i++)
    {
        sp_Push(st, -1);
    }
    st->Top = 0;
    int retVal;
    for(i = 1; i < (*theGraph)->M + 1; i++)
    {
        printf("trying to remove %d edges\n", i);
        if((retVal = generateBitsetAndHideEdges(i, 0, st, theGraph)) != 0)
        {
            return i; //minimum count of edges which failed to embed
        }
    }
}



/* main 
 * graph is read from a given file as parameter */
int main(int argc, char *argv[])
{
    graphP theGraph = gp_New();

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name");
        exit(1);
    }
    
    int edgesCount, vertexCount, i;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount, &vertexCount);

    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }

    gp_InitGraph(theGraph, vertexCount);
   
    for(i = 0; i < edgesCount; i++)
    {
        gp_AddEdge(theGraph, edgesList[i][0], 0, edgesList[i][1], 0);
    }

    clock_t begin, end;
    double time_spent;
    testGraph = gp_New();
    gp_InitGraph(testGraph, edgesCount);
    DOUBLED_EDGES_COUNT = edgesCount * 2;
    begin = clock();    
    //logic goes here
    int cr = getMinEdgesFailedToEmbed(&theGraph);
    printf("edges which cannot be dropped count - %d\n", cr);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);
    
    gp_Free(&theGraph);
    freeMem(edgesList, edgesCount); 
    return 0;
}

