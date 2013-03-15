
/* fileReader.h implementation file */

#include "fileReader.h"
#include "stdlib.h"
#include "stdio.h"

/* format of file:
    6
    15
    1 5 2 -1
    0 3 5 4 1 -1
    3 1 -1
    2 3 0 4 5 -1
    5 3 4 -1
    4 1 3 -1
*/

/* function to load graph from file to list of edges */
int ** readGraphFromFile(char * fileName, int * edgesCount, int * vertexCount)
{
    FILE * file = fopen(fileName, "r");
    int ** edgesList;

    if(file == NULL)
    {
        return NULL;
    }

    int j = 0, u, v;
    if(fscanf(file, "%d", edgesCount));
    if(fscanf(file, "%d", vertexCount));
    
    edgesList = malloc((*edgesCount)*sizeof(int*));
    
    if(!edgesList)
    {
        return NULL;
    }

    while(1)
    {
        if(fscanf(file, "%d", &u));
        if(u == -2)
        {
            break;
        }
        if(fscanf(file, "%d", &v));
        while(v != -1)
        {
            edgesList[j] = malloc(2*sizeof(int)); 
            edgesList[j][0] = u;
            edgesList[j++][1] = v;
            if(fscanf(file, "%d", &v));
        }
    }
    
    fclose(file);
    return edgesList;
}

