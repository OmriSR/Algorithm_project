#include "MST.h"

void MST::init(const Graph& i_graph, int* o_minEdgeToTreeFromVertex, MST::Parent* o_parent, bool* o_inTree)
{
	unsigned int numOfVertex = i_graph.getNumOfVertices();

	for (unsigned int i = 1; i < numOfVertex; ++i)		      /* min weight to tree initialazition*/
	{
		o_minEdgeToTreeFromVertex[i] = INFI;
		o_parent[i].m_myParent = NULL;
		o_parent[i].m_weightToParent = INFI;
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
	parent[treeRoot].m_myParent = -1;					/* the root has no parent*/
	parent[treeRoot].m_weightToParent = 0;

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
				updateParentArr(PQ_weightToTree, curNeighbour, minEdgeToTreeFromVertex, parent, curVertex);
			}
		}
	}

	return parent;
}

void MST::updateParentArr(PriorityQueue& o_PQ_weightToTree, const Graph::Edge& o_curNeighbour, int* o_minEdgeToTreeFromVertex, MST::Parent* o_parent, int o_curVertex)
{
	o_minEdgeToTreeFromVertex[o_curNeighbour.getDstVertex()] = o_curNeighbour.getWeight();
	o_parent[o_curNeighbour.getDstVertex()].m_myParent = o_curVertex;
	o_parent[o_curNeighbour.getDstVertex()].m_weightToParent = o_curNeighbour.getWeight();
	o_PQ_weightToTree.decreaseKey(o_curNeighbour.getDstVertex(), o_minEdgeToTreeFromVertex[o_curNeighbour.getDstVertex()]);
}

void MST::checkForMst(Parent* i_parentsArr, const Graph& i_g)
{
	for (int i = 0; i < i_g.getNumOfVertices(); ++i)
	{
		if (i_parentsArr[i].m_myParent == -1)
		{
			cout << "MST does not exist";
			exit(1);
		}
	}
}


vector<Graph::Edge> MST::kruskal(Graph& i_graph)
{	 /*-----------------INIT---------------*/
	int num_of_vertices = i_graph.getNumOfVertices();

	vector<Graph::Edge> Edges_Of_MST_ordered = i_graph.getuniqueEdges_Ordered();
	vector<Graph::Edge> result_MST(size_t(num_of_vertices) - 1);

	 Disjointed_sets Sets(num_of_vertices);
	 for (int i = 0; i < num_of_vertices; ++i)
			Sets.MakeSet(i);
	 /*--------------INIT END--------------*/
	 
	 for (const auto& Edge : Edges_Of_MST_ordered)
	 {
		 if (Sets.Find(Edge.getSrcVertex()) != Edge.getDstVertex())
		 {
			result_MST.emplace_back(Edge);
			Sets.Union(Edge.getSrcVertex(), Edge.getDstVertex());
		 }
	 }
	 return result_MST;
}
void MST::checkForMst(const vector<Graph::Edge>& edges_mst,int num_of_vertices)
{
	if (edges_mst.size() != (size_t(num_of_vertices) - 1))
	{
		cout << "MST does not exist";
		exit(1);
	}
}
