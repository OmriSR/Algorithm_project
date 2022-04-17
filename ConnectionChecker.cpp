#include "ConnectionChecker.h"

bool ConnectionChecker::dfs()
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
			if (dfsTreeCount == 0)
			{
				currentRoot = i;
				visit(vertexDataArr, i, currentRoot);
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

void ConnectionChecker::initVerticies(ConnectionChecker::VertexData* i_vertexDataArr)
{
	for (int i = 0; i < m_numOfVertices; ++i)
	{
		i_vertexDataArr[i].m_color = ConnectionChecker::colors::white;
		i_vertexDataArr[i].m_root = i;
	}
}

void ConnectionChecker::visit(VertexData* i_verticesDataArr,unsigned int i_vertexIndex, unsigned int i_currRoot)
{
	i_verticesDataArr[i_vertexIndex].m_root = i_currRoot;
	i_verticesDataArr[i_vertexIndex].m_color = colors::grey;

	unsigned int curNeighbourIndex;

	for (auto& curNeighbour : m_G.getVerticesVec()[i_vertexIndex].getEdgesToNeighbours())    /*Go through all current vertex neighbours (=dst vertex in edge) and look for a white vertex*/
	{
		curNeighbourIndex = curNeighbour.getDstVertex();

		if (i_verticesDataArr[curNeighbourIndex].m_color == colors::white)
		{
			visit(i_verticesDataArr, curNeighbourIndex, i_currRoot);
		}

		i_verticesDataArr[curNeighbourIndex].m_color = colors::black;
	}
}