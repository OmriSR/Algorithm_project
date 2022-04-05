#pragma once
#include "HeapNode.h"
#include <iostream>
#include <utility>
#include "Edge.h"

using namespace std;

class MinHeap
{
	class HeapNode
	{
		int m_vertexNum = 0;						//edge name  == data
		int m_weight = 0;						   //edge weight == key
//		Edge* m_dualPointer = nullptr;

	public:
		HeapNode(int i_vertexNum = 0, int i_weight = 0);
		int getVertexNum();
		void setVertexNum(int i_vertex_num);
		int getWeight();
		void setWeight(int i_newWeight);
//		void setDoualPtr(Edge* twinInEdgeArr);
		friend MinHeap;
	};

	HeapNode* m_heapArr = nullptr;
	int m_heapSize = 0, m_heapMaxSize = 0; /* = n-1*/  // the heap is constructed of all the edges from some vertex v in the graph to the current tree -> <= n-1 in a simple graph
	int* m_heapPtrArr = nullptr;
	bool m_allocated = false;

	int getLeftSon(int i_heapNode);

	int getRightSon(int i_heapNode);

	int getParent(int i_heapNode);

	void fixHeap(int i_heapNode);

	void updateHeapNodesDualPtr(const int& i_ind1, const int& i_ind2);

	void initHeapPtrArr(HeapNode* i_heapBaseArr, int i_size);

public:

	void build(HeapNode* i_heapBaseArr, int i_size);

	MinHeap(int i_numOfVertices);

	MinHeap(HeapNode* i_heapBaseArr, int i_size);

	~MinHeap();

	HeapNode* getHeap();

	HeapNode& deleteMin();

	void insert(HeapNode i_node);

	bool isEmpty();

	void decreaseKey(int i_nodeIndex, int i_newWeight);

	void climbUp(int i_node);

};