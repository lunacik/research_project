
/* In this approach we are trying to push as much edges as we can.
 * Result is the minimum number of edges which cause graph to be nonplanar */

#include <stdlib.h>
#include <time.h>
#include "graph.h" //from planarity project
#include "fileReader.h" //for loading graph from file
//#include "randomize.h" //for shuffling edges



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
    
    int edgesCount;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount);

    if(edgesList == NULL)
    {
        printf("reading from file failed\n");
        exit(1);
    }

    gp_InitGraph(theGraph, edgesCount);
    
    clock_t begin, end;
    double time_spent;

    begin = clock();    
    //logic goes here
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("time spent - %f\n", time_spent);

    freeMem(edgesList, edgesCount); 
    return 0;
}

