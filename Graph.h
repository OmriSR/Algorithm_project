#pragma once
#include <vector>
#include <set>
#include <list>
#include <iostream>
#include <stdlib.h>
using namespace std;

class Graph
{
public:
	class Edge
	{
		unsigned int                    m_src;
		unsigned int                    m_dst;
		std::set<unsigned int>  unordered_name;
		Edge* m_same_edge_undirected = nullptr;
		int m_weight = 0;
		bool m_ignore = false;
		bool m_isBridge;

		friend class Graph;
	public:
		Edge(unsigned int src = 0, unsigned int dst = 0, int weight = 0)
		{
			m_src =        src;
			m_dst =        dst;
			unordered_name.insert(src);
			unordered_name.insert(dst);
			m_weight =  weight;
			m_ignore =   false;
			m_isBridge = false;
		}
		int getWeight()
		{
			return m_weight;
		}
		void setWeight(const int& i_weight)
		{
			m_weight = i_weight;
		}
		bool operator<(const Edge& Other)
		{
			return m_weight < Other.m_weight;
		}//for sorting edges with kruskal
	};//END of Class Edge
private:
	class Vertex
	{
		unsigned int m_connected_component_Rep = 0;
		unsigned int         m_neighbors_count = 0;
		unsigned int              m_identifier = 0;
		list<Graph::Edge>			   m_EdgesToNeighbours;

		friend class Graph;
	public:
		Vertex(unsigned int id)
		{
			m_identifier = id;
			m_connected_component_Rep = id;
			m_neighbors_count = 0;
		}
	};//END of Class Vertex

	vector<Vertex> m_vertices;  

public:

	Graph(unsigned int num)
	{
		MakeEmpty(num);
	}

	void MakeEmpty(unsigned int Vertices);
	bool IsAdjacent(unsigned int i_u, unsigned int i_v);
	bool isVertexInNeighboursList(unsigned int i_u, unsigned int i_v);
	void AddEdge(unsigned int U, unsigned int V, int weight);
	//RemoveEdge(unsigned int U,unsigned int V)
	std::vector<Graph::Edge> GetAllEdges();
	const list<Graph::Edge>& GetAdjList(unsigned int U) { return m_vertices[U].m_EdgesToNeighbours; }
};

