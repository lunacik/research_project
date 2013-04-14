
#ifndef GREEDY_H_
#define GREEDY_H_

#include "graph.h"

int tryToAddEdge(graphD * theGraph, int u, int v);
int tryToEmbed(graphD * theGraph, int ** edgesList, int edgesCount, int * failedEdgesList);
int getEFTEC(int ** edgesList, int edgesCount, int ** edgesFailedToEmbedList, 
	std::vector<std::pair<int, int> > * edgesSucceedToEmbed, int iterations);


#endif
