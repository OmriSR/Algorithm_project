#include "Vertex.h"


template<class ID>
Vertex<ID>::Vertex(ID id)
{
	identifier = id;
	connected_component_Rep = id;
}

template<class ID>
Vertex<ID>::Vertex(ID id, unsigned int edgeNum) : Vertex(id)
{
	m_neighbors_count = edgeNum;
	//Edge.reserve(edgeNum);
}


