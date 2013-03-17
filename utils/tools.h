
#ifndef TOOLS_H
#define TOOLS_H


#include "graph.h"

void planarize_two_edges(graphP * theGraph, int u1, int v1, int u2, int v2, int newVertex);
void freeMem(int ** edgesList, int edgesCount);


#endif
