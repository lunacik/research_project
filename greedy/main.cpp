
#include "fileReader.h" //for loading graph from file
#include "tools.h"
#include <iostream>
#include "greedy.h"
#include "noname.h"
#include <vector>

/* main 
 * graph is read from a given file as parameter */
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: " << argv[0] << "file_name" << std::endl;
        exit(1);
    }
    
    int edgesCount, vertexCount, edgesFailedToEmbedCount;

    int ** edgesList = readGraphFromFile(argv[1], &edgesCount, &vertexCount);
    
    if(edgesList == NULL)
    {
        std::cout << "reading from file failed" << std::endl;
        exit(1);
    }

    int ** edgesFailedToEmbedList = (int**)malloc(edgesCount * sizeof(int*));
    for(int i = 0; i < edgesCount; i++)
    {
    	edgesFailedToEmbedList[i] = (int*)malloc(2 * sizeof(int));
    }
    
    edgesFailedToEmbedCount = getEFTEC(edgesList, edgesCount, edgesFailedToEmbedList);

    //std::cout << "Minimum count of edges which failed to embed - " <<
    //        edgesFailedToEmbedCount << std::endl;
   
    getCrossingNumber(edgesList, edgesCount,
    		edgesFailedToEmbedList, edgesFailedToEmbedCount, vertexCount);

    freeEdgesList(edgesList, edgesCount);
    freeEdgesList(edgesFailedToEmbedList, edgesCount);
    return 0;
}

