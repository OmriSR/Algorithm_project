#include "PriorityQueue.h"
#include "Graph.h"
#include "inputhandler.h"
#include "MST.h"
#include <fstream>
#include "ConnectionChecker.h"

void minHeapTest(int* i_arr, int i_vertexToDekey, int i_newWeight) {  // size is now hardcoded! needs to be change befor useage
	//int arr[4] = { 4,2,1,3 };

	cout << "The given array: " << '\n';
	for (int i = 0; i < 4; ++i)
	{
		i < 3 ? cout << i_arr[i] << ", " : cout << i_arr[i] << "." << '\n';
	}
	cout << '\n';

	//--------------- build heap----------------
	PriorityQueue pq(i_arr, 4);

	int* heapArr = new int[4];
	heapArr = pq.printPqArr();
	cout << "The min heap array for the arr given: " << '\n';
	for (int i = 0; i < 4; ++i)
	{
		i < 3 ? cout << heapArr[i] << ", " : cout << heapArr[i] << "." << '\n';
	}

	cout << '\n';
	//----------decrease key in index (vertexToDekey) to value (newWeight)---------------

	pq.deKey(i_vertexToDekey, i_newWeight);

	heapArr = pq.printPqArr();

	cout << "The min heap array after decreasing from vertex '" << i_vertexToDekey << "' to value " << i_newWeight << " is: " << '\n';
	for (int i = 0; i < 4; ++i)
	{
		i < 3 ? cout << heapArr[i] << ", " : cout << heapArr[i] << "." << '\n';
	}
}

int main(int argc,char** argv)
{//define inputhandler and outputhandler based on argv - TODO Gal
	Graph G;
	ConnectionChecker checker(G);

	if (checker.isConnected() == false)
	{
		cout << "invalid input - graph is not connected therefore no MST";
		exit(1);
	}
	
	MST::Parent* prim_result = MST::prim(G);
	vector<Graph::Edge> kruskal_result = MST::kruskal(G);
	
	MST::print_kruskal(kruskal_result);
	
	MST::print_prim(prim_result,G.getNumOfVertices()-1);

	G.removeEdge(inputhandler()(), inputhandler()());

	if (checker.isConnected() == false)
	{
		cout << "invalid input - graph is not connected, edge was a bridge";
		exit(1);
	}
	kruskal_result = MST::kruskal(G);
	MST::print_kruskal(kruskal_result);
}

