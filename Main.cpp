#include "Graph.h"
#include "io_handler.h"
#include "MST.h"
#include <fstream>
#include "ConnectionChecker.h"

ifstream inputhandler::input_file;
ofstream outputhandler::output_file;

int main(int argc,char** argv)
{
	inputhandler::openfile_toread(argv[1]);
	outputhandler::openfile_towrite(argv[2]);

	Graph G;
	ConnectionChecker checker(G);

	if (checker.isConnected() == false) outputhandler::exit_with_a_message("graph is not connected therefore no MST");
	
	MST::Parent* prim_result = MST::prim(G);
	vector<Graph::Edge> kruskal_result = MST::kruskal(G);
	
	outputhandler()(MST::print_kruskal(kruskal_result));
	
	outputhandler()(MST::print_prim(prim_result,G.getNumOfVertices()-1));

	system("pause");

	G.removeEdge(inputhandler()()-1, inputhandler()()-1);
	system("cls");

	if (checker.isConnected() == false) outputhandler::exit_with_a_message("invalid input - graph is not connected, edge was a bridge");
	
	kruskal_result = MST::kruskal(G);
	outputhandler()(MST::print_kruskal(kruskal_result));
	system("pause");
	inputhandler::closefile();
	outputhandler::closefile();
}

