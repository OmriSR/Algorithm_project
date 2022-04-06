#include "Graph.h"

using namespace std;

void Graph::MakeEmpty(unsigned int i_numOfVertices)
{
	m_vertices.reserve(i_numOfVertices);

	for (unsigned int i = 0; i < i_numOfVertices; ++i)   
	{
		m_vertices.emplace_back(Vertex(i));   // m_vetices[i] = Vertex(i) ??
	}
}

std::vector<Graph::Edge> Graph::GetAllEdges_Ordered()
{
	std::vector<Graph::Edge> AllEdgesVec = MakeUniqueEdgeVec();

	quicksort(AllEdgesVec, AllEdgesVec.begin(), AllEdgesVec.end());
	
	return AllEdgesVec;
}

std::vector<Graph::Edge> Graph::MakeUniqueEdgeVec()
{	
	long long vert_num = m_vertices.size();
	std::vector<Graph::Edge> AllEdgesVec;
	std::set<set<unsigned int>> AllEdgesSet;
	AllEdgesVec.reserve(vert_num*vert_num); //Worst case Nchoose2 edges  AllEdges.reserve(m_num_of_vertices * (m_num_of_vertices-1))

	for (const auto& V : m_vertices)
	{
		for (const auto& E : V.m_EdgesToNeighours)
			if (AllEdgesSet.end() != AllEdgesSet.find(E.unordered_name))
			{
				AllEdgesVec.emplace_back(E);
			}
	}

	AllEdgesVec.shrink_to_fit();

	return AllEdgesVec;
}


void Graph::quicksort(std::vector<Graph::Edge>& Edgevec, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right)
{
	if (Left >= Right) return;
	if (Edgevec.size() <= 1) return;

	std::vector<Graph::Edge>::iterator pivot = partition(Edgevec, Left, Right);
	quicksort(Edgevec, pivot + 1, Right);
	quicksort(Edgevec, Left, pivot - 1);
}
std::vector<Graph::Edge>::iterator Graph::partition(std::vector<Graph::Edge>& Edgevec, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right)
{
	std::vector<Graph::Edge>::iterator current = Right, pivot = Left;

	for (; current != pivot;)
	{
		if (current->getWeight() < pivot->getWeight())
		{
			std::swap(*current, *pivot);
			++current;
		}
		else if (current->getWeight() > pivot->getWeight())
		{
			std::swap(*current, *pivot);
			--current;
		}
	}
	return pivot;
}