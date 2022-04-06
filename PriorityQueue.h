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
};

