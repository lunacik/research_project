
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
		std::sort(face.begin(), face.end());
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


vertices_list getFaces(vertices_list dualGraph, int endVertex)
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


vertices_list getIncidentFaces(vertices_t face, vertices_list dualGraph)
{
	vertices_list incidentFaces;
	vertices_t tmpFace;

	for(vertices_list::iterator it = dualGraph.begin(); it != dualGraph.end(); it++)
	{
		std::set_intersection(it->begin(), it->end(),
			face.begin(), face.end(), std::back_inserter(tmpFace));

		if(tmpFace.size() == 2)
		{
			incidentFaces.push_back(*it);
		}

		tmpFace.clear();
	}

	return incidentFaces;
}


void findCommonEdge(vertices_t firstFace, vertices_t secondFace, int * u, int * v)
{
	vertices_t commonEdge;
	std::set_intersection(firstFace.begin(), firstFace.end(),
			secondFace.begin(), secondFace.end(), std::back_inserter(commonEdge));

	*u = commonEdge[0];
	*v = commonEdge[1];
}


void planarize_path(graphD * theGraph, int * edge, vertices_list * path, int * vertexCount)
{
	assert(path->size() > 1);
	int u, v;

	if(path->size() == 2)
	{
		findCommonEdge(path->at(1), path->at(0), &u, &v);
		planarize_two_edges(theGraph, u, v, edge[0], edge[1], *vertexCount);
		(*vertexCount)++;
	}
	else
	{
		for (vertices_list::reverse_iterator it = path->rbegin() ; it + 2 != path->rend(); ++it)
		{
			findCommonEdge(*it, *(it + 1), &u, &v);
			planarize_one_edge(theGraph, u, v, edge[0], *vertexCount);
			edge[0] = *vertexCount;
			(*vertexCount)++;
		}

		vertices_t ultimate = path->at(0);
		vertices_t penultimate = path->at(1);

		findCommonEdge(penultimate, ultimate, &u, &v);
		planarize_two_edges(theGraph, u, v, *vertexCount - 1, edge[1], *vertexCount);
		(*vertexCount)++;
	}

}


vertices_list backtrace(std::map<vertices_t, vertices_t> map, vertices_t e)
{
	vertices_t empty;
	vertices_list path;
	path.push_back(e);

	while(map[e] != empty)
	{
		e = map[e];
		path.push_back(e);
	}

	return path;
}


int getCrossingNumber(std::vector<std::pair<int, int> > * edgesSucceedToEmbed, int edgesCount,
		int ** edgesFailedToEmbedList, int edgesFailedToEmbedCount, int vertexCount)
{
	int cr = 0;

	graphD theGraph(vertexCount);

    for(int i = 0; i < edgesCount - edgesFailedToEmbedCount; i++)
    {
        add_edge(edgesSucceedToEmbed->at(i).first, edgesSucceedToEmbed->at(i).second, theGraph);
    }
	

    for(int i = 0; i < edgesFailedToEmbedCount; i++)
    {
    	vertices_list dualGraph = getDualGraph(theGraph);
    	vertices_list startFaces = getFaces(dualGraph, edgesFailedToEmbedList[i][0]);
    	vertices_list endFaces = getFaces(dualGraph, edgesFailedToEmbedList[i][1]);

    	std::deque<vertices_t> deq;
    	vertices_list closedFaces;
    	std::map<vertices_t, vertices_t> map;

    	for (vertices_list::iterator it = startFaces.begin() ; it != startFaces.end(); ++it)
    	{
    		deq.push_back(*it);
    		closedFaces.push_back(*it);
    	}

    	bool ok = false;
    	//BFS
    	while(!deq.empty())
    	{
    		vertices_t element = deq.front();
    		deq.pop_front();

        	for(vertices_list::iterator it = endFaces.begin() ; it != endFaces.end(); ++it)
        	{
        		if(*it == element)
        		{
        			ok = true;
        			break;
        		}
        	}
        	if(ok)
			{
        		vertices_list path = backtrace(map, element);
        		cr += path.size() - 1;
            	planarize_path(&theGraph, edgesFailedToEmbedList[i], &path, &vertexCount);
        		break;
			}

        	closedFaces.push_back(element);
        	vertices_list incidentFaces = getIncidentFaces(element, dualGraph);

        	for(vertices_list::iterator it = incidentFaces.begin() ; it != incidentFaces.end(); ++it)
        	{
        		bool found = false;
        		for(vertices_list::iterator itr = closedFaces.begin() ; itr != closedFaces.end(); ++itr)
        		{
        			if(*itr == *it)
        			{
        				found = true;
        				break;
        			}
        		}
        		if(!found)
        		{
        			deq.push_back(*it);
        			map[*it] = element;
        		}
        	}
    	}

    }


	return cr;
}

