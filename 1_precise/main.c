
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <time.h>
#include "graph.h" //from planarity project
#include "fileReader.h" //for loading graph from file



int use(stackP bitset, graphP * theGraph)
{
    int j = 0, arcPos;
    int i = bitset->S[j++];
    const int DOUBLED_EDGES_COUNT = (*theGraph)->M * 2;
 
    while(i != -1) //hiding edges
    {
        arcPos = DOUBLED_EDGES_COUNT + i * 2;
        gp_HideEdge(*theGraph, arcPos);
        i = bitset->S[j++];
    }
    graphP testGraph = gp_DupGraph(*theGraph);
    j = 0;
    i = bitset->S[j++];
    while(i != -1) //restoring edges
    {
        arcPos = DOUBLED_EDGES_COUNT + i * 2;
        gp_HideEdge(*theGraph, arcPos);
        gp_RestoreEdge(*theGraph, arcPos);
        i = bitset->S[j++];
    }    
    //checking if graph planar
    if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
    {
        gp_Free(&testGraph);
        return 1;
    }
    else
    {
        gp_Free(&testGraph);
        return 0;
    }
}


int go(int length, int start, stackP bitset, int edgesCount, graphP * theGraph)
{
    if(!length)
    {
        return use(bitset, theGraph);
    }
    int i, tmp = 0;
    for(i = start; i < edgesCount; i++)
    {
        sp_Push(bitset, i);
        if((tmp = go(length - 1, i + 1, bitset, edgesCount, theGraph) != 0))
        {
            return tmp;
        }
        bitset->S[--bitset->Top];
    }
}


int doIt(graphP * theGraph, int edgesCount)
{
    stackP st;
    st = sp_New(edgesCount);
    int i;
    for(i = 0; i < edgesCount; i++)
    {
        sp_Push(st, -1);
    }
    st->Top = 0;
    int tmp;
    for(i = 1; i < edgesCount + 1; i++)
    {
        if((tmp = go(i, 0, st, edgesCount, theGraph)) != 0)
        {
            return i;
        }
    }
}



/* main 
 * graph is read from a given file as parameter*/
int main(int argc, char *argv[])
{
    graphP theGraph = gp_New();

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name");
        exit(1);
    }
    
    int edgesCount, i;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount);

    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }

    gp_InitGraph(theGraph, edgesCount);
   
    for(i = 0; i < edgesCount; i++)
    {
        gp_AddEdge(theGraph, edgesList[i][0], 0, edgesList[i][1], 0);
    }

    clock_t begin, end;
    double time_spent;

    begin = clock();    
    //logic goes here
    int cr = doIt(&theGraph, edgesCount);
    printf("edges which cannot be dropped count - %d\n", cr);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);
    
    gp_Free(&theGraph);
    freeMem(edgesList, edgesCount); 
    return 0;
}

