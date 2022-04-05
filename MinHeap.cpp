#include "MinHeap.h"

MinHeap::HeapNode::HeapNode(int i_vertexNum = 0, int i_weight = 0)
{
	m_vertexNum = i_vertexNum;
	i_weight = m_weight;
}

int MinHeap::HeapNode::getVertexNum()
{
	return m_vertexNum;
}

void MinHeap::HeapNode::setVertexNum(int i_vertex_num)
{
	m_vertexNum = i_vertex_num;
}

int MinHeap::HeapNode::getWeight()
{
	return m_weight;
}

void MinHeap::HeapNode::setWeight(int i_newWeight)
{
	m_weight = i_newWeight;
}

void MinHeap::HeapNode::setDoualPtr(Edge* twinInEdgeArr)
{
	m_dualPointer = twinInEdgeArr;
}

int MinHeap::getLeftSon(int i_heapNode)
{
	return (2 * i_heapNode + 1);
}

int MinHeap::getRightSon(int i_heapNode)
{
	return (2 * i_heapNode + 2);
}

int MinHeap::getParent(int i_heapNode)
{
	return (i_heapNode - 1) / 2;
}

void MinHeap::fixHeap(int i_heapNode)
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

void MinHeap::updateHeapNodesDualPtr(const int& i_ind1, const int& i_ind2)
{
	m_heapPtrArr[i_ind1] = i_ind2;
	m_heapPtrArr[i_ind2] = i_ind1;
}

void MinHeap::initHeapPtrArr(HeapNode* i_heapBaseArr, int i_size)
{
	m_heapPtrArr = new int[i_size];

	for (int i = 0; i < i_size; ++i)
	{
		i_heapBaseArr[i] = i;
	}
}

void MinHeap::build(HeapNode* i_heapBaseArr, int i_size)
	{
		MinHeap(i_heapBaseArr, i_size);
	}

MinHeap::MinHeap(int i_numOfVertices)
	{
		m_heapMaxSize = i_numOfVertices;
		m_heapArr = new HeapNode[m_heapMaxSize];
		m_allocated = true;
	}

MinHeap::MinHeap(HeapNode* i_heapBaseArr, int i_size)
	{
		m_heapMaxSize = m_heapSize = i_size;

		m_heapArr = i_heapBaseArr;

		for (int i = 0; i < i_size; ++i)
		{
			m_heapArr[i].getVertexNum();
		}

		initHeapPtrArr(m_heapArr, i_size);

		for (int i = (i_size / 2 - 1); i >= 0; --i)
		{
			fixHeap(i);
		}
	}

MinHeap::~MinHeap()
{
	if (m_allocated == true)
	{
		delete[] m_heapArr;
		delete[] m_heapPtrArr;
		m_allocated = false;
	}
}

MinHeap::HeapNode* MinHeap::getHeap()
	{
		return m_heapArr;
	}

MinHeap::HeapNode& MinHeap::deleteMin()
	{
		if (m_heapSize < 1);//handle error

		HeapNode min = m_heapArr[0];

		m_heapArr[0] = m_heapArr[--m_heapSize];
		fixHeap(0);
		return min;
	}

void MinHeap::insert(HeapNode i_node)
	{
		if (m_heapSize == m_heapMaxSize) /*handle error*/;

		int heapIndex = m_heapSize++;

		while (heapIndex > 0 && m_heapArr[getParent(heapIndex)].getWeight() > i_node.getWeight())
		{
			m_heapArr[m_allocated] = m_heapArr[getParent(heapIndex)];
			heapIndex = getParent(heapIndex);
		}
	}

bool MinHeap::isEmpty()
	{
		return m_heapSize == 0;
	}

void MinHeap::decreaseKey(int i_nodeIndex, int i_newWeight)
{
	int heapNodeIndex = m_heapPtrArr[i_nodeIndex];
	m_heapArr[heapNodeIndex] = i_newWeight;
	climbUp(heapNodeIndex);
}

void MinHeap::climbUp(int i_node)
{	
	bool nodeInPlace = false;

	while ((i_node > 1) && (nodeInPlace = false))
	{
		if (m_heapArr[i_node].getWeight() < m_heapArr[getParent(i_node)].getWeight())
		{
			swap(m_heapArr[i_node], m_heapArr[getParent(i_node)]);
			updateHeapNodesDualPtr(i_node, getParent(i_node));
			i_node = getParent(i_node);
		}
		else
		{
			nodeInPlace = true;
		}
	}
}