
#include "fileReader.h"
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
    
    std::vector<std::pair<int, int> > * edgesSucceedToEmbed = new std::vector<std::pair<int, int> >;

    clock_t begin, end;
    double time_spent;
    
    begin = clock();

    edgesFailedToEmbedCount = getEFTEC(edgesList, edgesCount, edgesFailedToEmbedList, edgesSucceedToEmbed, 10);

    int cr = getCrossingNumber(edgesSucceedToEmbed, edgesCount,
    		edgesFailedToEmbedList, edgesFailedToEmbedCount, vertexCount);

    end = clock();
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "time spent - " << time_spent << std::endl;
    std::cout << "edges failed to embed count - " << edgesFailedToEmbedCount << std::endl;
    std::cout << "crossing number - " << cr << std::endl;
    
	delete edgesSucceedToEmbed;
    freeEdgesList(edgesList, edgesCount);
    freeEdgesList(edgesFailedToEmbedList, edgesCount);
    
    return 0;
}

