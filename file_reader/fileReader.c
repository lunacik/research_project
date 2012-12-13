
/* fileReader.h implementation file */

#include "fileReader.h"
#include "stdlib.h"
#include "stdio.h"

/* format of file:
    6
    1 5 2 -1
    0 3 5 4 1 -1
    3 1 -1
    2 3 0 4 5 -1
    5 3 4 -1
    4 1 3 -1
*/

/* function to load graph from file to list of edges */
int readGraphFromFile(char * fileName, int edgesList[][2])
{
    FILE * file = fopen(fileName, "r");
    
    if(file == NULL)
    {
        return 0;
    }

    int edgesCount, vertexCount, i = 0, j = 0, u, v;
    fscanf(file, "%d", &edgesCount);
    fscanf(file, "%d", &vertexCount);

    for(i = 0; i < vertexCount; i++)
    {
        fscanf(file, "%d", &u);
        fscanf(file, "%d", &v);

        while(v != -1)
        {
            edgesList[j][0] = u;
            edgesList[j++][1] = v;

            fscanf(file, "%d", &v);
        }
    }

    return 1;
}


/* function to get edges count of graph */
int getEdgesCount(char * fileName)
{
    FILE * file = fopen(fileName, "r");
    int edgesCount;
    fscanf(file, "%d", &edgesCount);
    return edgesCount;
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


