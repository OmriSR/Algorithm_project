#pragma once
class Disjointed_sets
{
private:
	class setNode
	{
		unsigned int size;
		unsigned int parent;
		friend class Disjointed_sets;
	};
	setNode* set = nullptr;
	bool homogenous = false;//When there is nothing left to union
public:
	Disjointed_sets(unsigned int size);
	~Disjointed_sets();
	void Union(unsigned int x, unsigned int y);
	void MakeSet(unsigned int x) { set[x].size = 1; set[x].parent = x; }
	unsigned int Find(unsigned int x);
};

