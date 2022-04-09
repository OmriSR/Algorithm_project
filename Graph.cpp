#include "Graph.h"

void Graph::MakeEmpty(unsigned int i_numOfVertices)
{
	m_vertices.reserve(i_numOfVertices);
	
	for (unsigned int i = 0; i < i_numOfVertices; ++i)   
	{
		m_vertices.emplace_back(Vertex(i));
	}
}

std::vector<Graph::Edge> Graph::GetAllEdges_Ordered()
{

	std::vector<Graph::Edge> AllEdgesVec = MakeUniqueEdgeVec();


	Graph::quicksort(AllEdgesVec, AllEdgesVec.begin(), AllEdgesVec.end());
	
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
		if (curNeighbour.m_dst == i_vertexToFind)
		{
			return true;
		}
	}
}

void Graph::quicksort(std::vector<Graph::Edge>& Edgevec, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right)
{
	if (Left >= Right) return;
	if (Edgevec.size() <= 1) return;

	std::vector<Graph::Edge>::iterator pivot = partition(Edgevec, Left, Right);
	quicksort(Edgevec, pivot + 1, Right);
	quicksort(Edgevec, Left, pivot - 1);
}

vector<Graph::Edge>::iterator Graph::partition(std::vector<Graph::Edge>& Edgevec, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right)
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

void Graph::addEdge(unsigned int i_uInd, unsigned int i_vInd, unsigned int i_weight)
{
	newEdgeValidityCheck(i_uInd, i_vInd, i_weight);

	m_vertices[i_uInd].m_EdgesToNeighbours.emplace_back(Edge(i_uInd, i_vInd, i_weight));
	m_vertices[i_vInd].m_EdgesToNeighbours.emplace_back(Edge(i_vInd, i_uInd, i_weight));

	connectEdgesPtrInAdjList(i_uInd, i_vInd);
}

void Graph::removeEdge(unsigned int i_u, unsigned int i_v)
{
	list<Edge>::iterator toRemoveItr;

	(i_u > -1) ?																											   // if i_u is a valid index
		findEdgeInAdjacentList(m_vertices[i_u].m_EdgesToNeighbours.begin(), m_vertices[i_u].m_EdgesToNeighbours.end(), i_v)	  //(u,v) - find iterator to edge that needs to be removes
		: toRemoveItr = m_vertices[i_u].m_EdgesToNeighbours.end();															 //if not a propper massage will be printed to console from metod removeEdgeValidityCheck
	
	removeEdgeValidityCheck(i_u, i_u, toRemoveItr);

	Edge identicalEdgeToRemove = *(*toRemoveItr).m_same_edge_undirected;  /* (v,u) - undirected graph*/

	m_vertices[i_v].m_EdgesToNeighbours.remove(identicalEdgeToRemove);    
	m_vertices[i_u].m_EdgesToNeighbours.erase(toRemoveItr);
}

list<Graph::Edge>::iterator Graph::findEdgeInAdjacentList(list<Graph::Edge>::iterator i_first, list<Graph::Edge>::iterator i_last, unsigned int i_ajacent)
{
	for (; i_first != i_last; ++i_first)
	{
		if ((*i_first).getDestination() == i_ajacent)
		{
			return i_first;
		}
	}
	return i_last;
}

void Graph::connectEdgesPtrInAdjList(unsigned int i_uInd, unsigned int i_vInd)
{
	Edge& u_v = m_vertices[i_uInd].m_EdgesToNeighbours.back();
	Edge& v_u = m_vertices[i_vInd].m_EdgesToNeighbours.back();

	u_v.m_same_edge_undirected = &(v_u);
	v_u.m_same_edge_undirected = &(u_v);
}

bool Graph::removeEdgeValidityCheck(unsigned int i_u, unsigned int i_v, list<Graph::Edge>::iterator i_edgeItr)
{
	try {
		if (i_edgeItr == m_vertices[i_u].m_EdgesToNeighbours.end()) { throw not_a_vertex; }
		if (i_u < 0 || i_v < 0) { throw(negative_vertex); }
		if ((isNumAnInt(i_u) && isNumAnInt(i_v) == false)) { throw(not_int); }
		if ((isVertexInRange(i_v, 1, m_vertices.size()) && isVertexInRange(i_u, 1, m_vertices.size()) == false)) { throw(vertex_out_of_range); }
	}
	catch (int i_error)
	{
		switch (i_error)
		{
		case 1:
			cout << "The vertices must be a non-negative!";
			break;
		case 2:
			cout << "The vertices must be an integer!";
			break;
		case 3:
			cout << "The vertices must be in between 1 and " << m_vertices.size();
			break;
		case 4:
			cout << "The given edge does not exist";
			break;
		default:
			cout << "An error occurred.";
			break;
		}
		exit(1);
	}
}

bool Graph::newEdgeValidityCheck(unsigned int i_uInd, unsigned int i_vInd, unsigned int i_weight)
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
			cout << "The vertices must be in between 1 and " << m_vertices.size();
			break;
		default:
			cout << "An error occurred.";
			break;
		}
		exit(1);
	}
}

bool Graph::isNumAnInt(int i_vertex)   //// needs to be a string format to check if float with out auto casting
{
	return (typeid(i_vertex).name() == typeid(int).name());
}

bool Graph::isVertexInRange(int i_vertex, int i_start, int i_end)
{
	return (i_vertex <= i_end && i_vertex >= i_start);
}





