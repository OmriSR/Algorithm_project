#include "ConnectionChecker.h"

unsigned int ConnectionChecker::dfs()
{
	VertexData* vertexDataArr = new VertexData[m_numOfVertices];
	unsigned int currentRoot;   
	unsigned int dfsTreeCount = 0;

	initVerticies(vertexDataArr);

	for (int i = 0; i < m_numOfVertices; ++i)
	{
		if (vertexDataArr[i].m_color == colors::white)
		{
			++dfsTreeCount;
			currentRoot = i;
			visit(vertexDataArr, i, currentRoot);

		}
	}
	return dfsTreeCount;

}

void ConnectionChecker::initVerticies(VertexData* i_vertexDataArr)
{
	for (int i = 0; i < m_numOfVertices; ++i)
	{
		i_vertexDataArr[i].m_root = i;
	}
}

void ConnectionChecker::visit(VertexData* i_verticesDataArr,unsigned int i_vertexIndex, unsigned int i_currRoot)
{
	i_verticesDataArr[i_vertexIndex].m_root = i_currRoot;
	i_verticesDataArr[i_vertexIndex].m_color = colors::grey;

	unsigned int curNeighbourIndex;

	for (const auto& curNeighbour : m_G.getVerticesVec()[i_vertexIndex].getEdgesToNeighbours())    /*Go through all current vertex neighbours (=dst vertex in edge) and look for a white vertex*/
	{
		curNeighbourIndex = curNeighbour.getDstVertex();

		if (i_verticesDataArr[curNeighbourIndex].m_color == colors::white)
		{
			visit(i_verticesDataArr, curNeighbourIndex, i_currRoot);
		}
	}
	i_verticesDataArr[i_vertexIndex].m_color = colors::black;

}