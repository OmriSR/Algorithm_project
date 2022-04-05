#pragma once
#include <utility>
#include <vector>
#include "Graph.h"


void quicksort(std::vector<Graph::Edge>& lst, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right);
std::vector<Graph::Edge>::iterator partition(std::vector<Graph::Edge>& lst, std::vector<Graph::Edge>::iterator Left, std::vector<Graph::Edge>::iterator Right);