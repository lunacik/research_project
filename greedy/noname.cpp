
#include "graph.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/ref.hpp>
#include <vector>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include "tools.h"

using namespace boost;

struct Edge
{
public:
	int u, v;

	Edge(int u, int v)
	{
		this->u = u;
		this->v = v;
	}

	bool operator== (const Edge& e)
	{
		return (e.u == u && e.v == v) || (e.v == u && e.u == v);
	}
};


typedef std::vector<Edge> edges_t;
typedef std::vector<int> vertices_t;
typedef std::vector<std::vector<int> > vertices_list;


struct Face
{
	edges_t edges;
	vertices_t vertices;
	int id;
	bool isClosed;

	Face(edges_t edges, vertices_t vertices, int id)
	{
		this->edges = edges;
		this->vertices = vertices;
		this->id = id;
		this->isClosed = false;
	}

	bool operator== (const Face& f)
	{
		return f.id == id;
	}
};


typedef std::vector<Face> faces_list;


struct output_visitor : public planar_face_traversal_visitor
{
	faces_list dualGraph;
	edges_t edges;
	vertices_t vertices;
	int maxId;

	output_visitor()
	{
		this->maxId = 0;
	}

	void begin_face()
	{
		edges = edges_t();
		vertices = vertices_t();
	}

	void end_face()
	{
		dualGraph.push_back(Face(edges, vertices, maxId++));
	}

	template <typename Vertex>
	void next_vertex(Vertex v)
	{
		vertices.push_back(v);
	}

	template <typename E>
	void next_edge(E e)
	{
		edges.push_back(Edge(e.m_source, e.m_target));
	}
};


faces_list getDualGraph(graphD g, int vertexCount)
{
	  property_map<graphD, edge_index_t>::type e_index = get(edge_index, g);
	  graph_traits<graphD>::edges_size_type edge_count = 0;
	  graph_traits<graphD>::edge_iterator ei, ei_end;
	  for(boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
	    put(e_index, *ei, edge_count++);

	  typedef std::vector< graph_traits<graphD>::edge_descriptor > vec_t;
	  std::vector<vec_t> embedding(vertexCount);
	  boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,
			  boyer_myrvold_params::embedding = &embedding[0]);

	  output_visitor v_vis;
	  planar_face_traversal(g, &embedding[0], v_vis);

	  return v_vis.dualGraph;
}


std::vector<int> getFaces(faces_list dualGraph, int vertex)
{
    std::vector<int> facesIds;

	for (faces_list::iterator it = dualGraph.begin() ; it != dualGraph.end(); ++it)
	{
		for(vertices_t::iterator itr = it->vertices.begin(); itr != it->vertices.end(); itr++)
		{
			if(*itr == vertex)
			{
				facesIds.push_back(it->id);
				break;
			}
		}
	}

	return facesIds;
}


std::vector<int> getAdjacentFaces(Face face, faces_list dualGraph)
{
	std::vector<int> facesIds;

	for(faces_list::iterator it = dualGraph.begin(); it != dualGraph.end(); it++)
	{
		if(it->isClosed || face == *it)
		{
			continue;
		}

		for(edges_t::iterator itr = it->edges.begin(); itr != it->edges.end(); itr++)
		{
			for(edges_t::iterator iter = face.edges.begin(); iter != face.edges.end(); iter++)
			{
				if(*iter == *itr)
				{
					facesIds.push_back(it->id);
				}
				continue;
			}
		}
	}

	return facesIds;
}


void findCommonEdge(Face firstFace, Face secondFace, int * u, int * v)
{
	for(edges_t::iterator it = firstFace.edges.begin(); it != firstFace.edges.end(); it++)
	{
		for(edges_t::iterator itr = secondFace.edges.begin(); itr != secondFace.edges.end(); itr++)
		{
			if(*it == *itr)
			{
				*u = it->u;
				*v = it->v;
				return;
			}
		}
	}
}


void planarize_path(graphD * theGraph, int * edge, faces_list * path, int * vertexCount)
{
	int u, v;

	if(path->size() == 2)
	{
		findCommonEdge(path->at(1), path->at(0), &u, &v);
		planarize_two_edges(theGraph, u, v, edge[0], edge[1], *vertexCount);
		(*vertexCount)++;
	}
	else
	{
		for(faces_list::reverse_iterator it = path->rbegin() ; it + 2 != path->rend(); ++it)
		{
			findCommonEdge(*it, *(it + 1), &u, &v);
			planarize_one_edge(theGraph, u, v, edge[0], *vertexCount);
			edge[0] = (*vertexCount)++;
		}

		findCommonEdge(path->at(1), path->at(0), &u, &v);
		planarize_two_edges(theGraph, u, v, *vertexCount - 1, edge[1], *vertexCount);
		(*vertexCount)++;
	}
}


faces_list backtrace(std::map<int, int> map, int lastFaceId, faces_list dualGraph)
{
	faces_list path;
	path.push_back(dualGraph[lastFaceId]);

	while(map[lastFaceId] != -1)
	{
		lastFaceId = map[lastFaceId];
		path.push_back(dualGraph[lastFaceId]);
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
    	faces_list dualGraph = getDualGraph(theGraph, vertexCount);
        std::vector<int> startFaces = getFaces(dualGraph, edgesFailedToEmbedList[i][0]);
        std::vector<int> endFaces = getFaces(dualGraph, edgesFailedToEmbedList[i][1]);

        std::deque<Face> deq;
    	faces_list closedFaces;
    	std::map<int, int> map;

    	for (std::vector<int>::iterator it = startFaces.begin() ; it != startFaces.end(); ++it)
    	{
    		dualGraph[*it].isClosed = true;
    		deq.push_back(dualGraph[*it]);
    		map[*it] = -1;
    	}

    	bool found = false;
    	//BFS
    	while(!deq.empty())
    	{
    		Face element = deq.front();
    		deq.pop_front();

        	for(std::vector<int>::iterator it = endFaces.begin() ; it != endFaces.end(); ++it)
        	{
        		if(*it == element.id)
        		{
        			found = true;
        			break;
        		}
        	}

        	if(found)
			{
        		faces_list path = backtrace(map, element.id, dualGraph);
        		cr += path.size() - 1;
            	planarize_path(&theGraph, edgesFailedToEmbedList[i], &path, &vertexCount);
        		break;
			}

        	std::vector<int> adjacentFaces = getAdjacentFaces(element, dualGraph);

        	for(std::vector<int>::iterator it = adjacentFaces.begin() ; it != adjacentFaces.end(); ++it)
        	{
				dualGraph[*it].isClosed = true;
				deq.push_back(dualGraph[*it]);
				map[*it] = element.id;
        	}

    	}
    }

    return cr;
}
