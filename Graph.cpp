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
	unsigned int u_numOfNeighbours = m_vertices[i_uInd].m_neighbors_count;
	unsigned int v_numOfNeighbours = m_vertices[i_vInd].m_neighbors_count;
	
	return u_numOfNeighbours > v_numOfNeighbours ? isVertexInNeighboursList(i_uInd, i_vInd) : isVertexInNeighboursList(i_vInd, i_uInd);
}

bool Graph::isVertexInNeighboursList(unsigned int i_vertexToFind, unsigned int i_neighboursListVertex)
{
	for (const auto& curNeighbour : m_vertices[i_neighboursListVertex].m_EdgesToNeighbours)
	{
		if (curNeighbour.m_src == i_vertexToFind)
		{
			return true;
		}
	}
}

void Graph::AddEdge(unsigned int i_uInd, unsigned int i_vInd, int weight)
{
	if (isVertexInNeighboursList(i_uInd, i_vInd) == true)
	{
		cout << "The vertex (" << i_uInd << "," << i_vInd << ") already exist in the graph!";
		exit(1);
	}
	//negetivity check! (validation)
}
