#include "Edge.h"


void quicksort(std::vector<Graph::Edge>& Edgevec, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right)
{
	if (Left >= Right) return;
	if (Edgevec.size() <= 1) return;
	
	std::vector<Graph::Edge>::iterator pivot = partition(Edgevec, Left, Right);
	quicksort(Edgevec, pivot + 1, Right);
	quicksort(Edgevec, Left, pivot - 1);
}
std::vector<Graph::Edge>::iterator partition(std::vector<Graph::Edge>&Edgevec , std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right)
{
	std::vector<Graph::Edge>::iterator current = Right, pivot = Left;

	for (;current!=pivot;)
	{
		if (current->getWeight() < pivot->getWeight())
		{
			std::swap(*current, *pivot);
			++current;
		}
		else if(current->getWeight() > pivot->getWeight())
		{
			std::swap(*current, *pivot);
			--current;
		}
	}
	return pivot;
}