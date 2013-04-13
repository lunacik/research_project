
#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
//#include <boost/property_map/property_map.hpp>

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_index_t, int> > graphP;

typedef adjacency_list
  < vecS,
    vecS,
    undirectedS,
    property<vertex_index_t, int>,
    property<edge_index_t, int>
  >
  graphD;

#endif
