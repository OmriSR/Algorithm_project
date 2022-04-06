#include "Graph.h"

void Graph::MakeEmpty(unsigned int Vertices)
{
	m_num_of_vertices = Vertices;
	m_vertices.reserve(Vertices);
	for (unsigned int i = 0; i < Vertices; ++i) m_vertices.emplace_back(Vertex(i));
}

std::vector<Graph::Edge> Graph::GetAllEdges()
{
	std::vector<Graph::Edge> AllEdges;
	AllEdges.reserve(m_num_of_vertices * m_num_of_vertices); //Worst case n^2 edges
	for (const auto& V : m_vertices)
		AllEdges.insert(AllEdges.end(), V.m_Edges.begin(), V.m_Edges.end());
	
	AllEdges.shrink_to_fit();

	return AllEdges;
}