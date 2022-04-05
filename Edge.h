#pragma once
class Edge
{
	pair<int, int> m_name;
	int m_weight = 0;
	HeapNode* m_dualPointer = nullptr;
	bool m_ignore = false;
	bool m_isBridge;

public:


	int getWeight()
	{
		return m_weight;
	}

	void setWeight(const int& i_weight)
	{
		m_weight = i_weight;
	}

	void setDualPointer(HeapNode* i_memAddress)
	{
		m_dualPointer = i_memAddress;
	}

	HeapNode* getDualPointer()
	{
		return m_dualPointer;
	}
};

