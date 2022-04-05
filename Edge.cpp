#include "Edge.h"


void quicksort(std::vector<Edge>& Edgevec, std::vector<Edge>::iterator Left, std::vector<Edge>::iterator Right)
{
	if (Left >= Right) return;
	
	std::vector<Edge>::iterator pivot = partition(Edgevec, Left, Right);
	quicksort(Edgevec, pivot + 1, Right);
	quicksort(Edgevec, Left, pivot - 1);
}
std::vector<Edge>::iterator partition(std::vector<Edge>&Edgevec , std::vector<Edge>::iterator Left, std::vector<Edge>::iterator Right)
{
	std::vector<Edge>::iterator current = Right, pivot = Left;

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