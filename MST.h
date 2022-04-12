#pragma once
#include "Graph.h"
#include "Disjointed_sets.h"
#include "PriorityQueue.h"

enum infinity{INFI = LONG_MAX};

class MST
{

public:
	struct Parent {
		unsigned int m_myParent;    /* to recreat the tree after algorithm is over*/
		int m_weightToParent;		  /* to calculate whole tree weight*/
	};

	static Parent* prim(const Graph& i_graph);
	static void checkForMst(Parent* i_parentsArr, const Graph& i_g);

private:
	static void init(const Graph& i_graph, int* o_minEdgeToTreeFromVertex, Parent* o_parent, bool* o_inTree);
	static void updateParentArr(PriorityQueue& o_PQ_weightToTree, const Graph::Edge& o_curNeighbour, int* o_minEdgeToTreeFromVertex, MST::Parent* o_parent, int o_curVertex);
};

