#include "MST.h"

void MST::init(const Graph& i_graph, int* o_minEdgeToTreeFromVertex, MST::Parent* o_parent, bool* o_inTree)
{
	unsigned int numOfVertex = i_graph.getNumOfVertices();

	for (int i = 1; i < numOfVertex; ++i)		      /* min weight to tree initialazition*/
	{
		o_minEdgeToTreeFromVertex[i] = INFI;
		o_parent[i].myParent = NULL;
		o_parent[i].weightToParent = INFI;
		o_inTree[i] = false;
	}
}

MST::Parent* MST::prim(const Graph& i_graph)
{
	unsigned int numOfVertex = i_graph.getNumOfVertices();
	bool* inTree = new bool[numOfVertex];				  /* boolean array indicating whether a node is in the tree or not*/

	int* minEdgeToTreeFromVertex = new int[numOfVertex];
	Parent* parent = new Parent[numOfVertex];

	int treeRoot = 0;									 /*Arbitrary choice of starting index*/

	minEdgeToTreeFromVertex[treeRoot] = 0;				/* roots self-distanse to tree is zero*/
	parent[treeRoot].myParent = NULL;					/* the root has no parent*/
	parent[treeRoot].weightToParent = 0;

	init(i_graph, minEdgeToTreeFromVertex, parent, inTree);

	PriorityQueue PQ_weightToTree(minEdgeToTreeFromVertex, numOfVertex);  //build heap using ctor

	while (PQ_weightToTree.isEmpty() == false)
	{
		int curVertex = PQ_weightToTree.getMinWeightVertex();
		inTree[curVertex] = true;

		for (auto& curNeighbour : i_graph.getVerticesVec()[curVertex].getEdgesToNeighbours())   /// goes through all of curVertex neighbours.
		{
			int weightOfEdgeToCurNeighbour = curNeighbour.getWeight();
		
			bool term1 = weightOfEdgeToCurNeighbour < minEdgeToTreeFromVertex[curNeighbour.getDstVertex()];
			bool term2 = (inTree[curNeighbour.getDstVertex()] == 0);

			if (term1 && term2)   /* if edge (currVertex(inTree),currNeighbour(outTree))'s weight is less then the weight updated in the minWeightToTree arr*/
			{
				updateParentAndWeight(PQ_weightToTree, curNeighbour, minEdgeToTreeFromVertex, parent, curVertex);
			}
		}
	}

	return parent;
}

void MST::updateParentAndWeight(PriorityQueue& o_PQ_weightToTree, const Graph::Edge& o_curNeighbour, int* o_minEdgeToTreeFromVertex, MST::Parent* o_parent, int o_curVertex)
{
	o_minEdgeToTreeFromVertex[o_curNeighbour.getDstVertex()] = o_curNeighbour.getWeight();
	o_parent[o_curNeighbour.getDstVertex()].myParent = o_curVertex;
	o_parent[o_curNeighbour.getDstVertex()].weightToParent = o_curNeighbour.getWeight();
	o_PQ_weightToTree.decreaseKey(o_curNeighbour.getDstVertex(), o_minEdgeToTreeFromVertex[o_curNeighbour.getDstVertex()]);
}