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
		cout << "invalid input:Number of vertices must be positive!";
		error = true;
	}
	else if (i_numOfVertices == 0)
	{
		cout << "invalid input:Empty graph given!";
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

std::vector<Graph::Edge> Graph::getuniqueEdges_Ordered() 
{
	if (!isordered)
	{
		Graph::quicksort(m_edges_unique, m_edges_unique.begin(), m_edges_unique.end());
		isordered = true;
	}
	return m_edges_unique;
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
	unsigned int same_edge_different_list_indx;
	vector<Edge>::const_iterator edge_itr = m_vertices[i_u].getEdgesToNeighbours().begin(),end_of_list = m_vertices[i_u].getEdgesToNeighbours().end();
	for (;edge_itr != end_of_list;++edge_itr)
	{
		if (edge_itr->getDstVertex() == i_v )
		{
			same_edge_different_list_indx = edge_itr->m_index_in_dst_neighbours_list;
			break;
		}
	}
	removeEdgeValidityCheck(i_u, i_v, edge_itr);
	const_cast<vector<Graph::Edge>&>(m_vertices[i_u].getEdgesToNeighbours()).erase(edge_itr);
	vector<Edge>::const_iterator  david = m_vertices[i_v].getEdgesToNeighbours().begin() + same_edge_different_list_indx;
	const_cast<vector<Graph::Edge>&>(m_vertices[i_v].getEdgesToNeighbours()).erase(david);
	
 //if i_u is a valid index ? (u,v) - find iterator to edge that needs to be removes : else a propper massage will be printed to console from metod removeEdgeValidityCheck
	// vector<Edge>::iterator toRemoveItr = (i_u >= 0) ?
	//	findEdgeInAdjacentList(m_vertices[i_u].m_EdgesToNeighbours.begin(), m_vertices[i_u].m_EdgesToNeighbours.end(), i_v):
	//	m_vertices[i_u].m_EdgesToNeighbours.end();

	//removeEdgeValidityCheck(i_u, i_v, toRemoveItr);

	//vector<Edge>::iterator identicalEdgeToRemoveItr = toRemoveItr->m_same_edge_undirected;  /* (v,u) - undirected graph*/

	///*remove edge from unique edge vector*/
	//for (int i = 0; i < m_edges_unique.size(); ++i)
	//{
	//	if (m_edges_unique[i].m_src == i_v + 1 && m_edges_unique[i].m_dst == i_u + 1) m_edges_unique.erase(m_edges_unique.begin()+i);
	//}
	//m_vertices[i_v].m_EdgesToNeighbours.erase(identicalEdgeToRemoveItr); 
	//m_vertices[i_u].m_EdgesToNeighbours.erase(toRemoveItr);
}

vector<Graph::Edge>::iterator Graph::findEdgeInAdjacentList(const vector<Graph::Edge>::iterator& i_first,const vector<Graph::Edge>::iterator& i_last, unsigned int i_ajacent)
{
	vector<Edge>::iterator runner = i_first;
	for (; runner != i_last; ++runner)
	{
		if (runner->getDestination() == i_ajacent)
		{
			return runner;
		}
	}
	return i_last;
}

void Graph::connectEdgesPtrInAdjList(unsigned int i_uInd, unsigned int i_vInd)
{
	unsigned int index_of_V_in_Uneighbours = m_vertices[i_uInd].m_EdgesToNeighbours.size()-1;
	unsigned int index_of_U_in_Vneighbours = m_vertices[i_vInd].m_EdgesToNeighbours.size()-1;

	prev(m_vertices[i_uInd].m_EdgesToNeighbours.end())->m_index_in_dst_neighbours_list = index_of_U_in_Vneighbours;
	prev(m_vertices[i_vInd].m_EdgesToNeighbours.end())->m_index_in_dst_neighbours_list = index_of_V_in_Uneighbours;
}

void Graph::removeEdgeValidityCheck(int i_u, int i_v, vector<Graph::Edge>::const_iterator i_edgeItr)
{
	int vec_size = m_vertices.size();
	try {
		if (i_edgeItr == m_vertices[i_u].m_EdgesToNeighbours.end()) { throw not_a_vertex; }
		if (i_u < 0 || i_v < 0) { throw(negative_vertex); }
		if ((isVertexInRange(i_v, vec_size) && isVertexInRange(i_u,vec_size )) == false) { throw(vertex_out_of_range); }
	}
	catch (error& i_error)
	{
		switch (i_error)
		{
		case 1:
			cout << "invalid input:The vertices must be a non-negative!";
			break;
		case 3:
			cout << "invalid input:The vertices must be in between 1 and " << m_vertices.size();
			break;
		case 4:
			cout << "invalid input:The given edge does not exist";
			break;
		default:
			cout << "invalid input:An error occurred.";
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
			cout << "invalid input";
			break;
		case 1:
			cout << "invalid input:The vertices must be a non-negative!";
			break;
		case 3:
			cout << "invalid input:The vertices must be in between 1 and " << m_vertices.size() << ".";
			break;
		default:
			cout << "invalid input:An error occurred.";
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
	m_edges_unique.reserve(num);
	unsigned int U, V;
	int weight;
	for (unsigned int i = 0; i < num; ++i)
	{
		addEdge((weight = input()),(V=(input()-1)), (U=(input()-1)));	  // -1 bias since vertices expected in range [1,n]
		m_edges_unique.push_back({ U, V, weight });	  // but will be treated in range [0,n-1] because... computers...
	} 							     			 
	for (auto& vert : m_vertices) vert.m_EdgesToNeighbours.shrink_to_fit();

	if (num == 0)
	{
		m_notconnected = true;
	}
}

void Graph::validateNumOfEdges(unsigned int num)
{
	if (num < 0)
	{
		cout << "invalid input:Number of edges must me positive!";
		exit(1);
	}
	if (m_vertices.size() == 1 && num != 0)
	{
		cout << "invalid input:not a Simple graph";
		exit(1);
	}
	if (num < m_vertices.size()-1)
	{
		m_notconnected = true;
	}
}



