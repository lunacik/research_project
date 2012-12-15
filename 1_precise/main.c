
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <time.h>
#include "graph.h" //from planarity project
#include "fileReader.h" //for loading graph from file


int f(graphP * theGraph, int edgesCount)
{
    int i;
    
    graphP testGraph = gp_DupGraph(*theGraph);

    if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
    {
        return 0;
    }

    gp_Free(&testGraph);
    for(i = 0; i < edgesCount; i++)
    {
        gp_HideEdge(*theGraph, 2 * edgesCount + i);
        testGraph = gp_DupGraph(*theGraph);

        if(gp_Embed(testGraph, EMBEDFLAGS_PLANAR) != NONPLANAR)
        {
            return 1;
        }
        gp_Free(&testGraph);
        gp_RestoreEdge(*theGraph, 2 * edgesCount + i);
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

    printf("edges which cannot be dropped count - %d\n", f(&theGraph, edgesCount));

    //gp_HideEdge(theGraph, 20016);
    //gp_RestoreEdge(theGraph, 20016);
    //printf("%s\n", gp_Embed(theGraph, EMBEDFLAGS_PLANAR) ? "not planar" : "planar");

    /*
    clock_t begin, end;
    double time_spent;

    begin = clock();    
    //logic goes here
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);
    */
    gp_Free(&theGraph);
    freeMem(edgesList, edgesCount); 
    return 0;
}

