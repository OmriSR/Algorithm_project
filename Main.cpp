#include <iostream>
#include "PriorityQueue.h"
#include "inputhandler.h"
#include "Graph.h"

using namespace std;

void minHeapTest(int* i_arr, int i_vertexToDekey, int i_newWeight);

int main()
{

	vector<Graph::Edge> testvec;
	//debug qs
	testvec.push_back(Graph::Edge(1, 2, 200));
	testvec.push_back(Graph::Edge(1, 4, 5));
	testvec.push_back(Graph::Edge(2, 4, 300));
	testvec.push_back(Graph::Edge(3, 4, -5));
	testvec.push_back(Graph::Edge(2, 3, 0));
	testvec.push_back(Graph::Edge(2, 6, -300));
	Graph::quicksort(testvec, testvec.begin(), testvec.end());
	for (int i = 0; i < 5; ++i)
		cout << testvec[i].getWeight() << endl;

	cout << inputhandler()();
	int arr[4] = { 4,2,1,-3 };
	minHeapTest(arr, 1, 1);

}

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
