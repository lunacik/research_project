
#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>


using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int> > graphP;


#endif
