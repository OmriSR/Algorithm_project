#pragma once
template <class ID>
class Vertex
{
	ID identifier;
	ID connected_component_Rep;
	unsigned int m_neighbors_count;
	//vector<Edge> Edges;
public:
	Vertex(ID id);
	Vertex(ID id, unsigned int edgeNum);

};

