
#ifndef GREEDY_H_
#define GREEDY_H_

#include "graph.h"

int tryToAddEdge(graphP * theGraph, int u, int v);
int tryToEmbed(graphP * theGraph, int ** edgesList, int edgesCount, int * failedEdgesList);
int getEFTEC(int ** edgesList, int edgesCount, int ** edgesFailedToEmbedList);


#endif
