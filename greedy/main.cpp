
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
        <<  "-t, -e, -m, -n greedy_iterations_count, -l, -d]" << std::endl;
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
    bool lessVerbose = false;
    bool distributedTime = false;
    
    while ((option = getopt(argc, argv,"f:i:temn:ld")) != -1) 
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
             case 'l':  lessVerbose = true;
                 break;
             case 'd': distributedTime = true;
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

    clock_t begin, end, cbegin = 0, cend = 0, ebegin = 0, eend = 0;
    double time_spent;
    
	int minEFTEC = 0;
	
    begin = clock();
	//MAIN BODY
    
	
    for(int i = 0; i < iterationsCount; i++)
    {
        ebegin = clock();
		edgesFailedToEmbedCount = getEFTEC(edgesList, edgesCount, 
			edgesFailedToEmbedList, edgesSucceedToEmbed, greedyIterations);
        eend = clock();
        //std::cout << edgesFailedToEmbedCount << std::endl;
	    cbegin = clock();
		int cr = getCrossingNumber(edgesSucceedToEmbed, edgesCount,
			edgesFailedToEmbedList, edgesFailedToEmbedCount, vertexCount);
	    cend = clock();
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
    if(lessVerbose)
    {
        std::cout << minCr << std::endl;
    }
    else
    {
        if(distributedTime)
        {
            std::cout << "time spent on EFTEC search - " << (double)(eend - ebegin) / CLOCKS_PER_SEC << std::endl;
            std::cout << "time spent on crossings search - " << (double)(cend - cbegin) / CLOCKS_PER_SEC << std::endl;
        } 
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
        
        std::cout << "average crossing number - " << (float)sumCr / iterationsCount << std::endl;
    }
	
	delete edgesSucceedToEmbed;
    freeEdgesList(edgesList, edgesCount);
    freeEdgesList(edgesFailedToEmbedList, edgesCount);
    
    return 0;
}

