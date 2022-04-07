#include "Graph.h"

using namespace std;

void Graph::MakeEmpty(unsigned int i_numOfVertices)
{
	m_vertices.reserve(i_numOfVertices);
	
	for (unsigned int i = 0; i < i_numOfVertices; ++i)   
	{
		m_vertices.emplace_back(Vertex(i));
	}
}

std::vector<Graph::Edge> Graph::GetAllEdges()
{
	vector<Graph::Edge> AllEdges;
	//AllEdges.reserve(m_num_of_vertices * m_num_of_vertices); 

	for (const auto& V : m_vertices)
	//	AllEdges.insert(AllEdges.end(), V.m_Edges.begin(), V.m_Edges.end());
	
	AllEdges.shrink_to_fit();

	return AllEdges;
}

bool Graph::IsAdjacent(unsigned int i_uInd, unsigned int i_vInd)
{
	unsigned int u_numOfNeighbours = m_vertices[i_uInd].m_neighbours_count;
	unsigned int v_numOfNeighbours = m_vertices[i_vInd].m_neighbours_count;
	
	return u_numOfNeighbours > v_numOfNeighbours ? isVertexInNeighboursList(i_uInd, i_vInd) : isVertexInNeighboursList(i_vInd, i_uInd);
}

bool Graph::isVertexInNeighboursList(unsigned int i_vertexToFind, unsigned int i_neighboursListVertex)
{
	for (const auto& curNeighbour : m_vertices[i_neighboursListVertex].m_EdgesToNeighbours)
	{
		if (curNeighbour == m_vertices[i_vertexToFind])
		{
			return true;
		}
	}
}

void Graph::AddEdge(unsigned int i_uInd, unsigned int i_vInd, int i_weight)
{
	newEdgeValidityCheck(i_uInd, i_vInd, i_weight);

	m_vertices[i_uInd].m_EdgesToNeighbours.emplace_back(Edge(i_uInd, i_vInd, i_weight));
	m_vertices[i_vInd].m_EdgesToNeighbours.emplace_back(Edge(i_vInd, i_uInd, i_weight));

}

bool Graph::newEdgeValidityCheck(unsigned int i_uInd, unsigned int i_vInd, int i_weight)
{
	try
	{
		if (isVertexInNeighboursList(i_uInd, i_vInd) == true) {throw(not_a_new_edge);}
		if (i_uInd < 0 || i_vInd < 0) {throw(negative_vertex);}
		if ((isNumAnInt(i_uInd) && isNumAnInt(i_vInd) && isNumAnInt(i_weight)) == false) {throw(not_int);}
		if ((isVertexInRange(i_vInd, 1, m_vertices.size()) && isVertexInRange(i_uInd, 1, m_vertices.size()) == false)) {throw(vertex_out_of_range);}
	}
	catch (int i_error)
	{
		switch (i_error)
		{
		case 0:
			cout << "The vertex (" << i_uInd << "," << i_vInd << ") already exist in the graph!";
			break;
		case 1:
			cout << "The vertices must be a non-negative!";
			break;
		case 2:
			cout << "The vertices and weight must be an integer!";
			break;
		case 3:
			cout << "The vertices must be in between 1 and n";
			break;
		default:
			cout << "An error occurred.";
			break;
		}
		exit(1);
	}
}

bool Graph::isNumAnInt(int i_vertex)
{
	return (typeid(i_vertex).name() == typeid(int).name());
}

bool Graph::isVertexInRange(int i_vertex, int i_start, int i_end)
{
	return (i_vertex <= i_end && i_vertex >= i_start);
}

