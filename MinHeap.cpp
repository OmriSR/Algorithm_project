#include "MinHeap.h"

MinHeap::HeapNode::HeapNode(int i_vertexNum, int i_weight)
{
	m_vertexNum = i_vertexNum;
	i_weight = m_weightToTree;
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
	return m_weightToTree;
}

void MinHeap::HeapNode::setWeight(int i_newWeight)
{
	m_weightToTree = i_newWeight;
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
	else
	{
		min = i_heapNode;
	}
	if (rightSon < m_heapSize && m_heapArr[rightSon].getWeight() < m_heapArr[min].getWeight())
	{
		min = rightSon;
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

void MinHeap::build(int* i_verticesWeightToTreeArr, int i_size)
{
	m_heapMaxSize = m_heapSize = i_size;
	m_heapArr = new HeapNode[i_size];
	m_heapPtrArr = new int[i_size];
	m_allocated = true;

	for (int i = 0; i < i_size; ++i)
	{
		m_heapArr[i].setVertexNum(i);
		m_heapArr[i].setWeight(i_verticesWeightToTreeArr[i]);
		m_heapPtrArr[i] = i;  // when heap created all vertices in given arr are arranged that vertex t is in index t of the given weight arr
	}

	//initHeapPtrArr(m_heapArr, i_size);

	for (int i = (i_size / 2 - 1); i >= 0; --i)
	{
		fixHeap(i);
	}
}

MinHeap::MinHeap(int* i_verticesWeightToTreeArr, int i_size)
{
	build(i_verticesWeightToTreeArr, i_size);
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

unsigned int MinHeap::deleteMin()           // returns  index
{
	if (m_heapSize < 1)
	{
		cout << "trying to access empty heap!";
		exit(1);
	}

	HeapNode min = m_heapArr[0];

	m_heapArr[0] = m_heapArr[--m_heapSize];
	fixHeap(0);
	return min.getVertexNum();
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
	m_heapArr[heapNodeIndex].setWeight(i_newWeight);
	climbUp(heapNodeIndex);
}

void MinHeap::climbUp(int i_node)
{
	bool nodeInPlace = false;

	while ((i_node >= 1) && (nodeInPlace == false))
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