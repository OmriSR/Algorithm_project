#pragma once
#include "Graph.h"
#include "Disjointed_sets.h"
#include "PriorityQueue.h"

enum infinity{INFI = LONG_MAX};
constexpr short NONE = -1;

class MST
{

public:
	struct Parent {
		unsigned int m_myParent;    /* to recreat the tree after algorithm is over*/
		int m_weightToParent;		  /* to calculate whole tree weight*/
	};

	static Parent* prim(const Graph& i_graph);
	static vector<Graph::Edge> kruskal(Graph& i_graph);
	static void checkForMst(Parent* i_parentsArr, const Graph& i_g);//REMOVE
	static void checkForMst(const vector<Graph::Edge>& , int);//REMOVE

	static void print_prim(const Parent* i_P, const unsigned int i_edgeCount)
	{
		unsigned int treeWeight = 0;

		for (int i = 0; i <= i_edgeCount; ++i)
		{
			treeWeight += i_P[i].m_weightToParent;
		}
		cout << endl << "Prim: " << treeWeight;
	}


	static void print_kruskal(const vector<Graph::Edge>& Tree)
	{
		unsigned int treeWeight = 0;
		system("cls");
		for (const auto& Edge : Tree) treeWeight += Edge.getWeight();

		cout << endl << "Kruskal: " << treeWeight;
	}

private:
	static void init(const Graph& i_graph, int* o_minEdgeToTreeFromVertex, Parent* o_parent, bool* o_inTree);
	static void updateParentArr(PriorityQueue& o_PQ_weightToTree, const Graph::Edge& o_curNeighbour, int* o_minEdgeToTreeFromVertex, MST::Parent* o_parent, int o_curVertex);
};

