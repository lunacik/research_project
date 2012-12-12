
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "graph.h" //from planarity project
#include "time.h"




void shuffleEdges(int edgesList[][2], int edgesCount)
{
    int i;
    int j;
    int tmp1, tmp2;

    srand(time(NULL));
    for(i = edgesCount - 1; i >= 0; i--)
    {
        j = rand() % edgesCount;
        tmp1 = edgesList[i][0];
        tmp2 = edgesList[i][1];
        edgesList[i][0] = edgesList[j][0];
        edgesList[i][1] = edgesList[j][1];
        edgesList[j][0] = tmp1;
        edgesList[j][1] = tmp2;
    }
}

/*
void write_to_file(char * filename, int array[][2], int n)
{
    FILE * file = fopen(filename, "w");
    int i = 0;
    for(; i < n; i++)
    {
        fprintf(file, "%d %d\n", array[i][0], array[i][1]);
    }
    fclose(file);
}
*/

int add_edge(graphP * theGraph, int u, int v)
{
    graphP g = gp_DupGraph(*theGraph);
    gp_AddEdge(g, u, 0, v, 0);
    int Result = gp_Embed(g, EMBEDFLAGS_PLANAR);
    if(Result != NONPLANAR)
    {
        gp_AddEdge(*theGraph, u, 0, v, 0);
    }
    gp_Free(&g);
    return Result;
}



int firstTime(graphP * theGraph, int edgesList[][2], int edgesCount)
{
    int i = 0;
    int failed = 0;

    for(; i < edgesCount; i++)
    {
        if(add_edge(theGraph, edgesList[i][0], edgesList[i][1]) == NONPLANAR)
        {
            failed++;
        }
    }
    return failed;
}


int main(int argc, char *argv[])
{
    graphP theGraph = gp_New();

    if(argc < 2)
    {
        printf("%s %s\n", argv[0], "file_name [mode]");
    }

    FILE * file = fopen(argv[1], "r");
    
    if(file == NULL)
    {
        exit(1);
    }

    int edgesCount;
    fscanf(file, "%d", &edgesCount);
    gp_InitGraph(theGraph, edgesCount);
    int i = 0;
    int u, v;
    const int VERTEX_COUNT = edgesCount;
    int edgesList[VERTEX_COUNT][2];

    /*
    for(; i < edgesCount; i++)
    {
        fscanf(file, "%d", &u);
        fscanf(file, "%d", &v);
        edgesList[i][0] = u;
        edgesList[i][1] = v;
    }
    */
    for(; i < edgesCount;)
    {
        fscanf(file, "%d", &u);
        fscanf(file, "%d", &v);
        while(v != -1)
        {
            edgesList[i++][0] = u;
            edgesList[i++][1] = v;
            fscanf(file, "%d", &v);
        }
    }
    
    int min = 9999999;
    int lastNum;
    for(i = 0; i < 1; i++)
    {
        shuffleEdges(edgesList, edgesCount);
        lastNum = firstTime(&theGraph, edgesList, edgesCount);
        min = MIN(min, lastNum);
        gp_Free(&theGraph);
        theGraph = gp_New();
        gp_InitGraph(theGraph, edgesCount);
    } 

    printf("crossing number is - %d\n", min);

    /*
    for(i = 0; i < edgesCount; i++)
    {
        printf("Adding (%d, %d)", edgesList[i][0], edgesList[i][1]);
        //add_edge(&theGraph, u, v); 
        printf("%s\n", add_edge(&theGraph, edgesList[i][0], edgesList[i][1]) ? " - not planar" : " - planar");
    }
    */
    
    gp_Free(&theGraph);

    return 0;
}

