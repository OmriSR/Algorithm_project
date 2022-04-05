#pragma once
#include <utility>
#include <vector>

class Edge
{
	//std::pair<int, int> m_name;
	unsigned int src;
	unsigned int dst;
	int m_weight = 0;
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

	bool operator<(const Edge& Other) { return m_weight < Other.m_weight; }//for sorting edges with kruskal
};

void quicksort(std::vector<Edge>& lst, std::vector<Edge>::iterator Left, std::vector<Edge>::iterator Right);
std::vector<Edge>::iterator partition(std::vector<Edge>& lst, std::vector<Edge>::iterator Left, std::vector<Edge>::iterator Right);