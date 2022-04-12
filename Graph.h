#pragma once
#include "inputhandler.h"
#include <vector>
#include <set>
#include <list>
#include <ctype.h>
#include <string>

using namespace std;

enum  error{ not_a_new_edge, negative_vertex, not_int, vertex_out_of_range, not_a_vertex};

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
		inline Edge(unsigned int src = 0, unsigned int dst = 0, int weight = 0)
		{
			m_src = src;
			m_dst = dst;
			unordered_name.insert(src);
			unordered_name.insert(dst);
			m_weight = weight;
			m_ignore = false;
			m_isBridge = false;
		}
		inline unsigned int getDstVertex() const { return m_dst; }
		inline unsigned int getSrcVertex() const { return m_src; }
		inline int getWeight()const                         // both set and get method are unnecessary while Edge is public.
		{
			return m_weight;
		}
		inline void setWeight(const int& i_weight)
		{
			m_weight = i_weight;
		}
		inline bool operator<(const Edge& Other)
		{
			return m_weight < Other.m_weight;
		}//for sorting edges with kruskal
		friend inline bool operator==(const Edge& i_edge,const Edge& i_otherEdge) { return i_edge.m_dst == i_otherEdge.m_dst; }
		inline unsigned int getDestination() { return m_dst; }

	};//END of Class Edge

private:
	class Vertex
	{
		unsigned int m_connected_component_Rep = 0;
		unsigned int              m_identifier = 0;

		list<Edge>			   m_EdgesToNeighbours;

		friend class Graph;

	public:
		Vertex(unsigned int id)
		{
			m_identifier = id;
			m_connected_component_Rep = id;
		}

		inline const list<Edge>& getEdgesToNeighbours() const { return m_EdgesToNeighbours; }

	};//END of Class Vertex

	vector<Vertex> m_vertices;
	bool m_isForest = false;

	/*---------------private member functions---------------*/
	static void quicksort(std::vector<Graph::Edge>& edgevec, const std::vector<Graph::Edge>::iterator& Left, const std::vector<Graph::Edge>::iterator& Right);
	static std::vector<Graph::Edge>::iterator partition(std::vector<Graph::Edge>& lst,const  std::vector<Graph::Edge>::iterator& Left, const std::vector<Graph::Edge>::iterator& Right);
	std::vector<Graph::Edge> MakeUniqueEdgeVec();
	list<Graph::Edge>::iterator findEdgeInAdjacentList(list<Graph::Edge>::iterator i_first, list<Graph::Edge>::iterator i_last, unsigned int i_ajacent);

	void MakeEmpty(unsigned int i_numOfVertices);
	void SetGraphEdges(unsigned int num);

	bool IsAdjacent(unsigned int i_u, unsigned int i_v);
	bool isVertexInNeighboursList(unsigned int i_u, unsigned int i_v);
	bool isNumAnInt(const string& i_vertex);
	bool isVertexInRange(int i_vertex, int i_end);

	void addEdge(int i_weight, unsigned int i_v, unsigned int i_u);
	void connectEdgesPtrInAdjList(unsigned int i_uInd, unsigned int i_vInd);

	const std::list<Graph::Edge>& GetAdjList(unsigned int U) { return m_vertices[U].m_EdgesToNeighbours; }


	/*-----------validity checks---------------*/
	void validateNumOfVertices(unsigned int i_numOfVertices);
	void validateNumOfEdges(unsigned int num);
	void newEdgeValidityCheck(int i_uInd, int i_vInd, int i_weight);
	void removeEdgeValidityCheck(int i_u, int i_v, list<Graph::Edge>::iterator i_edgeItr);


public:
	Graph();
	std::vector<Graph::Edge> GetAllEdges_Ordered();
	inline int getNumOfVertices() const {  return  m_vertices.size(); }
	inline const vector<Vertex>& getVerticesVec() const { return m_vertices; }
	inline bool getIsForest() { return m_isForest; }
	void removeEdge(unsigned int i_u, unsigned int i_v);

};

