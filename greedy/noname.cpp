
#include "noname.h"
#include "cstdlib"
#include "graph.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/ref.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include "tools.h"
#include <algorithm>

using namespace boost;


typedef std::vector<int> vertices_t;
typedef std::vector<std::vector<int> > vertices_list;


struct output_visitor : public planar_face_traversal_visitor
{
	vertices_list dualGraph;
	vertices_t face;

	void begin_face()
	{
		face = vertices_t();
	}

	void end_face()
	{
		dualGraph.push_back(face);
	}

	template <typename Vertex>
	void next_vertex(Vertex v)
	{
		face.push_back(v);
	}
};



vertices_list getDualGraph(graphD g)
{
	  property_map<graphD, edge_index_t>::type e_index = get(edge_index, g);
	  graph_traits<graphD>::edges_size_type edge_count = 0;
	  graph_traits<graphD>::edge_iterator ei, ei_end;
	  for(boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	    put(e_index, *ei, edge_count++);

	  typedef std::vector< graph_traits<graphD>::edge_descriptor > vec_t;
	  std::vector<vec_t> embedding(num_vertices(g));
	  boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
			  boyer_myrvold_params::embedding = &embedding[0]);

	  output_visitor v_vis;
	  planar_face_traversal(g, &embedding[0], v_vis);

	  return v_vis.dualGraph;
}


int isFailed(int ** edgesFailedToEmbedList, int edgesFailedToEmbedCount, int * edge)
{
	for(int i = 0; i < edgesFailedToEmbedCount; i++)
	{
		if(edgesFailedToEmbedList[i][0] == edge[0] &&
				edgesFailedToEmbedList[i][1] == edge[1])
		{
			return true;
		}
	}
	return false;
}


vertices_list getEndVertices(vertices_list dualGraph, int endVertex)
{
	vertices_list endVertices;

	for (vertices_list::iterator it = dualGraph.begin() ; it != dualGraph.end(); ++it)
	{
		for(vertices_t::iterator itr = it->begin(); itr != it->end(); itr++)
		{
			if(*itr == endVertex)
			{
				endVertices.push_back(*it);
				break;
			}
		}
	}

	return endVertices;
}


vertices_list BFS(int startVertex, vertices_list endVertices,
		vertices_list dualGraph, vertices_list * visitedVertices)
{
	//if startVertex in endVertices ? return visitedVertices

	vertices_list start_vertices = getEndVertices(dualGraph, startVertex);

	for (vertices_list::iterator it = start_vertices.begin() ; it != start_vertices.end(); ++it)
		{
			for(vertices_t::iterator itr = it->begin(); itr != it->end(); itr++)
			{
				if(*itr == endVertex)
				{
					endVertices.push_back(*it);
					break;
				}
			}
		}
}


void findCommonEdge(vertices_t firstFace, vertices_t secondFace, int * u, int * v)
{
	vertices_t vec2;
	std::sort(firstFace.begin(), firstFace.end(), std::greater<int>());
	std::sort(secondFace.begin(), secondFace.end(), std::greater<int>());
	std::set_intersection(  firstFace.begin(), firstFace.end(),
			secondFace.begin(), secondFace.end(), vec2.begin());

	*u = vec2[0];
	*v = vec2[1];
}


void planarize_path(graphD * theGraph, int * edge, vertices_list path, int * vertexCount)
{
	for (vertices_list::iterator it = path.begin() ; it + 1 != path.end(); ++it)
	{
		int u, v;
		findCommonEdge(*it, *(it + 1), &u, &v);
		planarize_two_edges(theGraph, u, v, edge[0], edge[1], *vertexCount);
		(*vertexCount)++;

	}
}


int getCrossingNumber(int ** edgesList, int edgesCount,
		int ** edgesFailedToEmbedList, int edgesFailedToEmbedCount, int vertexCount)
{
	int cr = 0;

	graphD theGraph(vertexCount);

    for(int i = 0; i < edgesCount; i++)
    {
    	if(!isFailed(edgesFailedToEmbedList, edgesFailedToEmbedCount, edgesList[i]))
    	{
        	add_edge(edgesList[i][0], edgesList[i][1], theGraph);
    	}
    }


    /*
    for (vertices_list::iterator it = dualGraph.begin() ; it != dualGraph.end(); ++it)
    {
    	for(vertices_t::iterator itr = it->begin(); itr != it->end(); itr++)
    	{
    		std::cout << *itr << " ";
    	}
    	std::cout << std::endl;
    }
	*/


    for(int i = 0; i < edgesFailedToEmbedCount; i++)
    {
    	vertices_list dualGraph = getDualGraph(theGraph);
    	vertices_list endVertices = getEndVertices(dualGraph, edgesFailedToEmbedList[i][1]);
    	vertices_list * visitedVertices = new vertices_list;
    	vertices_list path =
    			BFS(edgesFailedToEmbedList[i][0], endVertices, dualGraph, visitedVertices);
		cr += path.size() - 1;
    	planarize_path(&theGraph, edgesFailedToEmbedList[i], path, &vertexCount);
    }


	return cr;
}

