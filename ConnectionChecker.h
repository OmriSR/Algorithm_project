#pragma once
#include "Graph.h"

constexpr short NO_VALUE = -1;

class ConnectionChecker
{
	enum class colors { white, grey, black };

	class VertexData
	{
		colors m_color = colors::white;
		int m_root = NO_VALUE;
		friend ConnectionChecker;
	};

	const Graph& m_G;
	const unsigned int m_numOfVertices = m_G.getNumOfVertices();

	void visit(VertexData* i_verticesDataArr, unsigned int i_vertexIndex, unsigned int i_currRoot);
	void initVerticies(VertexData* i_vertexDataArr);
	unsigned int dfs();

public:
	inline ConnectionChecker(Graph& i_G) : m_G(i_G) {};
	inline bool isConnected() { return (dfs() == 1); }
};

