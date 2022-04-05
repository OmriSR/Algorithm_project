#pragma once
#include <iostream>
#include <utility>
#include "Edge.h"

using namespace std;

class HeapNode
{
	int m_vertexNum=0;
//	pair<int,int> m_name;					//edge name  == data
	int m_weight=0;						   //edge weight == key
	Edge* m_dualPointer=nullptr;

public:

	HeapNode(int i_vertexNum, int i_weight)
	{
		m_vertexNum = i_vertexNum;
		i_weight = m_weight;
	}

	int getVertexNum()
	{
		return m_vertexNum;
	}

	void setVertexNum(int i_vertex_num)
	{
		m_vertexNum = i_vertex_num;
	}

	int getWeight()
	{
		return m_weight;
	}

	void setWeight(int i_newWeight)
	{
		m_weight = i_newWeight;
	}

	void setDoualPtr(Edge* twinInEdgeArr)
	{
		m_dualPointer = twinInEdgeArr;
	}





	/*HeapNode(const HeapNode& io_heapNode)   // shallow copy ctor works fine (?)
	{
		m_name = io_heapNode.m_name;
		m_weight = io_heapNode.m_weight;
		m_dualPointer = i
	}

	void swapHeapNodes(HeapNode& io_node)   //  stl swap is fine (?)
	{
		HeapNode tempNode = *this;
		*this = io_node;
		io_node = tempNode;
	}
	*/
};

