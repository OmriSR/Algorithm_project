#pragma once
#include "HeapNode.h"

class MinHeap
{
	HeapNode* m_heapArr = nullptr;
	int m_root = 0, m_heapSize = 0, m_heapMaxSize = 0; /* = n-1*/  // the heap is constructed of all the edges from some vertex v in the graph to the current tree -> <= n-1 in a simple graph
	Edge* m_edgesWeightsAndHeapPtr = nullptr;
	bool m_allocated = false;

	int getLeftSon(int i_heapNode)
	{
		return (2 * i_heapNode + 1);
	}

	int getRightSon(int i_heapNode)
	{
		return (2 * i_heapNode + 2);
	}

	int getParent(int i_heapNode)
	{
		return (i_heapNode - 1) / 2;
	}

	void fixHeap(int i_heapNode)
	{
		int min;
		int leftSon = getLeftSon(i_heapNode), rightSon = getRightSon(i_heapNode);

		if (leftSon < m_heapSize && m_heapArr[leftSon].getWeight() < m_heapArr[i_heapNode].getWeight())
		{
			min = leftSon;
		}
		else if (rightSon < m_heapSize && m_heapArr[rightSon].getWeight() < m_heapArr[i_heapNode].getWeight())
		{
			min = rightSon;
		}
		else
		{
			min = i_heapNode;
		}

		if (min != i_heapNode)
		{
			updateHeapNodesDualPtr(min, i_heapNode);

			swap(m_heapArr[min], m_heapArr[i_heapNode]);
			fixHeap(min);
		}
	}

	void updateHeapNodesDualPtr(const int& i_ind1, const int& i_ind2)
	{
		m_edgesWeightsAndHeapPtr[i_ind1].setDualPointer(m_heapArr + i_ind2);
		m_edgesWeightsAndHeapPtr[i_ind2].setDualPointer(m_heapArr + i_ind1);
	}

	void initEdgesWeightsAndHeapPtrArr(HeapNode* i_heapBaseArr, int i_size)
	{
		m_edgesWeightsAndHeapPtr = new Edge[i_size];

		for (int i = 0; i < i_size; ++i)
		{
			m_edgesWeightsAndHeapPtr[i].setWeight(i_heapBaseArr[i].getWeight());
			m_edgesWeightsAndHeapPtr[i].setDualPointer(i_heapBaseArr + i);   //sets pointer from helper arr to the ADDRESS IN THE HEAP ARR => every change of location in the heap needs to be updated in this section as well
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
		m_edgesWeights = new Edge[m_heapMaxSize ];
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

	~MinHeap()
	{
		if (m_allocated == true)
		{
			delete[] m_heapArr;
			delete[] m_edgesWeightsAndHeapPtr;
			m_allocated = false;
		}
	}

	HeapNode* getHeap()
	{
		return m_heapArr;
	}
	
	HeapNode& deleteMin()
	{
		if (m_heapSize < 1);//handle error
		
		HeapNode min = m_heapArr[0];
		
		m_heapArr[0] = m_heapArr[--m_heapSize];
		fixHeap(0);
		return min;
	}

	void insert(HeapNode i_node)
	{
		if (m_heapSize == m_heapMaxSize) /*handle error*/;
		
		int heapIndex = m_heapSize++;

		while (heapIndex > 0 && m_heapArr[getParent(heapIndex)].getWeight() > i_node.getWeight())
		{
			m_heapArr[m_allocated] = m_heapArr[getParent(heapIndex)];
			heapIndex = getParent(heapIndex);
		}
	}

	bool isEmpty()
	{
		return m_heapSize == 0;
	}

	void decreaseKey(int i_nodeIndex, int i_newWeight)
	{
		m_edgesWeightsAndHeapPtr[i_nodeIndex].setWeight(i_newWeight);
		HeapNode* nodeInHeap = m_edgesWeightsAndHeapPtr[i_nodeIndex].getDualPointer();
		nodeInHeap->setWeight(i_newWeight);
		fixHeap(nodeInHeap->getVertexNum());
	}
};

