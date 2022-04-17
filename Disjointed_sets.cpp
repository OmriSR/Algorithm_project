#include "Disjointed_sets.h"

Disjointed_sets::Disjointed_sets(unsigned int size)
{
	m_size = size;
	set = new setNode[size];
	for (unsigned int i = 0; i < size; ++i) MakeSet(i);//init forest of trees
	homogenous = false;
}
Disjointed_sets::~Disjointed_sets()
{
	delete[] set;
}

void Disjointed_sets::Union(unsigned int x, unsigned int y)
{//bysize
	if (set[x].size > set[y].size)
	{
		set[y].parent = x;
		set[x].size += set[y].size;
	}
	else
	{
		set[x].parent = y;
		set[y].size += set[x].size;
	}
}
unsigned int Disjointed_sets::Find(unsigned int x)
{//with path compression --- corrupts non-representitives node's size
	if (x == set[x].parent) return x;
	
	return set[x].parent = Find(set[x].parent);
}