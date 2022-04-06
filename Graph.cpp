#include "Graph.h"

using namespace std;

void Graph::MakeEmpty(unsigned int i_numOfVertices)
{
	m_num_of_vertices = i_numOfVertices;
	m_vertices.reserve(i_numOfVertices);

	for (unsigned int i = 0; i < i_numOfVertices; ++i)   
	{
		m_vertices.emplace_back(Vertex(i));   // m_vetices[i] = Vertex(i) ??
	}
}

std::vector<Graph::Edge> Graph::GetAllEdges()
{
	std::vector<Graph::Edge> AllEdges;
	AllEdges.reserve(m_num_of_vertices * m_num_of_vertices); //Worst case n^2 edges  AllEdges.reserve(m_num_of_vertices * (m_num_of_vertices-1))

	for (const auto& V : m_vertices)
	//	AllEdges.insert(AllEdges.end(), V.m_Edges.begin(), V.m_Edges.end());
	
	AllEdges.shrink_to_fit();

	return AllEdges;
}


