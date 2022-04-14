#include "Graph.h"


void Graph::MakeEmpty(unsigned int i_numOfVertices)
{
	validateNumOfVertices(i_numOfVertices);

	m_vertices.reserve(i_numOfVertices);
	
	for (unsigned int i = 0; i < i_numOfVertices; ++i)   
	{
		m_vertices.emplace_back(Vertex(i));
	}
}

void Graph::validateNumOfVertices(unsigned int i_numOfVertices)
{
	bool error = false;

	if (i_numOfVertices < 0)
	{
		cout << "Number of vertices must be positive!";
		error = true;
	}
	else if (i_numOfVertices == 0)
	{
		cout << "Empty graph given!";
		error = true;
	}

	if (error == true)
	{
		exit(1);
	}
}

Graph::Graph()
{
	inputhandler  input;
	MakeEmpty(input());

	SetGraphEdges(input());
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
		for (const auto& E : V.m_EdgesToNeighbours)
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
	unsigned int u_numOfNeighbours = m_vertices[i_uInd].m_EdgesToNeighbours.size();
	unsigned int v_numOfNeighbours = m_vertices[i_vInd].m_EdgesToNeighbours.size();
	
	return u_numOfNeighbours > v_numOfNeighbours ? isVertexInNeighboursList(i_uInd, i_vInd) : isVertexInNeighboursList(i_vInd, i_uInd);
}

bool Graph::isVertexInNeighboursList(unsigned int i_vertexToFind, unsigned int i_neighboursListVertex)
{
	for (const auto& curNeighbour : m_vertices[i_neighboursListVertex].m_EdgesToNeighbours)   // if empty begin() == end() and wont get in the loop (hopefully)
	{
		if (curNeighbour.m_dst == i_vertexToFind)
		{
			return true;
		}
	}
	return false;
}

void Graph::quicksort(std::vector<Graph::Edge>& Edgevec,const  std::vector<Graph::Edge>::iterator& Left, const std::vector<Graph::Edge>::iterator& Right)

{
	if (Left >= Right) return;
	if (Edgevec.size() <= 1) return;

	std::vector<Graph::Edge>::iterator pivot = partition(Edgevec, Left, Right);
	quicksort(Edgevec, Left, pivot);
	quicksort(Edgevec, pivot+1, Right);
}

std::vector<Graph::Edge>::iterator Graph::partition(std::vector<Graph::Edge>& Edgevec, const std::vector<Graph::Edge>::iterator& Left,const  std::vector<Graph::Edge>::iterator& Right)

{
	std::vector<Graph::Edge>::iterator pivot = std::prev(Right,1), moving_obj = Left;

	for (auto j = Left; j != pivot; ++j) {
		// bool format 
		if (*j<*pivot) {
			std::swap(*moving_obj++, *j);
		}
	}
	std::swap(*moving_obj, *pivot);
	return moving_obj;
}

void Graph::addEdge(int i_weight, unsigned int i_vInd, unsigned int i_uInd )
{	
	newEdgeValidityCheck(i_uInd, i_vInd, i_weight);
	
	m_vertices[i_uInd].m_EdgesToNeighbours.emplace_back(Edge(i_uInd, i_vInd, i_weight));
	m_vertices[i_vInd].m_EdgesToNeighbours.emplace_back(Edge(i_vInd, i_uInd, i_weight));
	
	connectEdgesPtrInAdjList(i_uInd, i_vInd);
}

void Graph::removeEdge(unsigned int i_u, unsigned int i_v)
{
	list<Edge>::iterator toRemoveItr;

// if i_u is a valid index ? (u,v) - find iterator to edge that needs to be removes : else a propper massage will be printed to console from metod removeEdgeValidityCheck
	toRemoveItr = (i_u >= 0) ?
		findEdgeInAdjacentList(m_vertices[i_u].m_EdgesToNeighbours.begin(), m_vertices[i_u].m_EdgesToNeighbours.end(), i_v):
		toRemoveItr = m_vertices[i_u].m_EdgesToNeighbours.end();

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

void Graph::removeEdgeValidityCheck(int i_u, int i_v, list<Graph::Edge>::iterator i_edgeItr)
{
	try {
		if (i_edgeItr == m_vertices[i_u].m_EdgesToNeighbours.end()) { throw not_a_vertex; }
		if (i_u < 0 || i_v < 0) { throw(negative_vertex); }
		if ((isVertexInRange(i_v, int(m_vertices.size()) && isVertexInRange(i_u, int(m_vertices.size())) == false))) { throw(vertex_out_of_range); }
	}
	catch (error& i_error)
	{
		switch (i_error)
		{
		case 1:
			cout << "The vertices must be a non-negative!";
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

void Graph::newEdgeValidityCheck(int i_u, int i_v, int i_weight)
{
	try
	{
		if (i_u < 0 || i_v < 0) { throw(negative_vertex); }
		else if (!(isVertexInRange(i_v, int(m_vertices.size()) - 1) && isVertexInRange(i_u, int(m_vertices.size() - 1)))) { throw(vertex_out_of_range); }
		else if (isVertexInNeighboursList(i_u, i_v) == true) throw(not_a_new_edge);
	}

	catch (error& i_error)
	{
		switch (i_error)
		{
		case 0:
			cout << "The vertex (" << i_u << "," << i_v << ") already exist in the graph!";
			break;
		case 1:
			cout << "The vertices must be a non-negative!";
			break;
		case 3:
			cout << "The vertices must be in between 1 and " << m_vertices.size() << ".";
			break;
		default:
			cout << "An error occurred.";
			break;
		}
		exit(1);
	}
}

bool Graph::isNumAnInt(const string& i_vertex)   //// needs to be a string format to check if float with out auto casting
{
	for (int i = 0; i < i_vertex.size(); ++i)
	{
		if (isdigit(i_vertex[i] == false))
		{
			return false;
		}
	}
	return true;
}

bool Graph::isVertexInRange(int i_vertex, int i_end)
{
	return (i_vertex <= i_end && i_vertex >= 0);
}

void Graph::SetGraphEdges(unsigned int num)
{
	inputhandler input;

	validateNumOfEdges(num);

	for (unsigned int i = 0; i < num; ++i)
	{
		addEdge(input(), input()-1, input()-1);   // -1 bias since vertices expected in range [1,n]
	} 							     			  // but will be treated in range [0,n-1] because... computers...


	if (num == 0)
	{
		m_notconnected = true;
	}
}

void Graph::validateNumOfEdges(unsigned int num)
{
	if (num < 0)
	{
		cout << "Number of edges must me positive!";
		exit(1);
	}
	if (m_vertices.size() == 1 && num != 0)
	{
		cout << "Simple graph is required -> no self edges allowed.";
		exit(1);
	}
	if (num < m_vertices.size()-1)
	{
		m_notconnected = true;
	}
}



