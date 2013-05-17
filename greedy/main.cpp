
#include "fileReader.h"
#include "tools.h"
#include <iostream>
#include "greedy.h"
#include "noname.h"
#include "randomize.h"
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>



void print_usage_and_exit()
{
	std::cout << "usage: greedy -f file_name [-i iterations_count, "
        <<  "-t, -e, -m, -n greedy_iterations_count]" << std::endl;
    exit(1);
}

/* main 
 * graph is read from a given file as parameter */
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        print_usage_and_exit();
    }
    
    int option = 0;
    int greedyIterations = 10;
    char fileName[255];
    bool isFileNameSet = false;
    int iterationsCount = 1;
    bool printTime = false;
    bool printEFTEC = false;
    bool printMinimumCr = false;
    
    while ((option = getopt(argc, argv,"f:i:temn:")) != -1) 
    {
        switch (option)
        {
             case 'f' : strcpy(fileName, optarg);
						isFileNameSet = true;
                 break;
             case 'i' : iterationsCount = atoi(optarg);
                 break;
             case 't' : printTime = true;
                 break;
             case 'e' : printEFTEC = true;
                 break;
             case 'm' : printMinimumCr = true;
                 break;
             case 'n' : greedyIterations = atoi(optarg);
				 break;
             default: print_usage_and_exit(); 
        }   
    }   
    
    if (!isFileNameSet)
    {
        print_usage_and_exit();
    }

    
    int edgesCount, vertexCount, edgesFailedToEmbedCount;
    int minCr = 9999999, sumCr = 0;

    int ** edgesList = readGraphFromFile(fileName, &edgesCount, &vertexCount);
    
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
	//MAIN BODY
	
    
	int minEFTEC = 0;
	
    for(int i = 0; i < iterationsCount; i++)
    {
		edgesFailedToEmbedCount = getEFTEC(edgesList, edgesCount, 
			edgesFailedToEmbedList, edgesSucceedToEmbed, greedyIterations);

		shuffleEdges(edgesSucceedToEmbed);
		
		int cr = getCrossingNumber(edgesSucceedToEmbed, edgesCount,
			edgesFailedToEmbedList, edgesFailedToEmbedCount, vertexCount);
			
		if(cr < minCr)
		{
			minCr = cr;
			minEFTEC = edgesFailedToEmbedCount;
		}
		
		sumCr += cr;
	}
	
	//END MAIN BODY
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	if(printTime)
	{
		std::cout << "time spent - " << time_spent << std::endl;
	}
	
	if(printEFTEC)
	{
		
		std::cout << "EFTEC - " << minEFTEC << std::endl;
	}
	
	if(printMinimumCr)
	{
		std::cout << "minimum crossing number - " << minCr << std::endl;
	}
	
	std::cout << "average crossing number - " << sumCr / iterationsCount << std::endl;
	
	
	delete edgesSucceedToEmbed;
    freeEdgesList(edgesList, edgesCount);
    freeEdgesList(edgesFailedToEmbedList, edgesCount);
    
    return 0;
}

