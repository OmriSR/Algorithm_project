#pragma once
#include "MinHeap.h"

class PriorityQueue // make tampleted 
{
	MinHeap m_myHeap;
public:
	PriorityQueue(int* i_verticesWeightFromTree, int i_size) : m_myHeap(i_verticesWeightFromTree, i_size){}

	int* printPqArr()
	{
		return m_myHeap.printHeapWeightsArr();
	}

	void deKey(int i_nodeIndex, int i_newWeight)
	{
		m_myHeap.decreaseKey(i_nodeIndex, i_newWeight);
	}

	inline bool isEmpty() { return m_myHeap.isEmpty(); }

	inline unsigned int getMinWeightVertex() { return m_myHeap.deleteMin(); }

	inline void decreaseKey(unsigned int i_node, int i_newWeight) { return m_myHeap.decreaseKey(i_node, i_newWeight); }
};

