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
		Edge* m_dualPointer = nullptr;

	public:
		HeapNode(int i_vertexNum = 0, int i_weight = 0);
		int getVertexNum();
		void setVertexNum(int i_vertex_num);
		int getWeight();
		void setWeight(int i_newWeight);
		void setDoualPtr(Edge* twinInEdgeArr);
		friend MinHeap;
	};

	HeapNode* m_heapArr = nullptr;
	int m_heapSize = 0, m_heapMaxSize = 0; /* = n-1*/  // the heap is constructed of all the edges from some vertex v in the graph to the current tree -> <= n-1 in a simple graph
	int* m_heapPtrArr = nullptr;  
	bool m_allocated = false;

	int getLeftSon(int i_heapNode);

	int getRightSon(int i_heapNode);

		if (min != i_heapNode)
		{

	void fixHeap(int i_heapNode);


	void initHeapPtrArr(HeapNode* i_heapBaseArr, int i_size);

		for (int i = 0; i < i_size; ++i)
		{
			m_edgesWeightsAndHeapPtr[i].setWeight(i_heapBaseArr[i].getWeight());
			i_heapBaseArr[i].setDoualPtr(m_edgesWeightsAndHeapPtr + i);
		}
	}

public:

	void build(HeapNode* i_heapBaseArr, int i_size)
	{
		MinHeap(i_heapBaseArr, i_size);
	}

	MinHeap(int i_numOfVertices)
	{
		m_heapMaxSize = i_numOfVertices - 1;
		m_heapArr = new HeapNode[m_heapMaxSize];
		m_edgesWeights = new Edge[m_heapMaxSize];
		m_allocated = true;
	}

	MinHeap(HeapNode* i_heapBaseArr, int i_size)
	{
		m_heapMaxSize = m_heapSize = i_size;

		m_heapArr = i_heapBaseArr;

		for (int i = 0; i < i_size; ++i)
		{
			m_heapArr[i].getVertexNum(i);
		}

		initEdgesWeightsAndHeapPtrArr(m_heapArr, i_size);

		for (int i = (i_size / 2 - 1); i >= 0; --i)
		{
			fixHeap(i);
		}	
	}

	MinHeap(int i_numOfVertices);

	MinHeap(HeapNode* i_heapBaseArr, int i_size);

	~MinHeap();

	HeapNode* getHeap();

	HeapNode& deleteMin();

	void insert(HeapNode i_node);

	bool isEmpty();

	void decreaseKey(int i_nodeIndex, int i_newWeight);

	void climbUp(int i_node);

	void decreaseKey(int i_nodeIndex, int i_newWeight)
	{
		m_edgesWeightsAndHeapPtr[i_nodeIndex].setWeight(i_newWeight);
		nodeInHeap->setWeight(i_newWeight);
		fixHeap(nodeInHeap->getVertexNum());
	}
};

