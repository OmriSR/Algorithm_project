#pragma once
#include "Graph.h"

class ConnectionChecker
{
	enum class colors { white, grey, black };

	class VertexData
	{
		colors m_color = colors::white;
		int m_root = -1;
		friend ConnectionChecker;
	};

	const Graph& m_G;
	const unsigned int m_numOfVertices = m_G.getNumOfVertices();

	void visit(VertexData* i_verticesDataArr, unsigned int i_vertexIndex, unsigned int i_currRoot);
	void initVerticies(VertexData* i_vertexDataArr);

public:


	unsigned int dfs();
};

