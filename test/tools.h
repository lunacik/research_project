
#ifndef TOOLS_H
#define TOOLS_H


#include "graph.h"

void planarize_two_edges(graphD * theGraph, int u1, int v1, int u2, int v2, int newVertex);
void planarize_one_edge(graphD * theGraph, int u1, int v1, int u2, int newVertex);
void freeEdgesList(int ** edgesList, int edgesCount);


#endif
