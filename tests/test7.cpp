#include "Graph.h"

//#include "../Graph.hpp"

// create a graph
// add 10000 -> 1 nodes
// delete 1 -> 5000 nodes
// add -5000 -> -1 nodes
// add edge -5000 to -1
// add edge -5000 to 5000
// print edges

int main() {
	
	gdwg::Graph<int,int> g;
	
	for (int i = 1000; i > 0; --i) {
		g.addNode(i);
	}
	
	for (int i = 0; i < 500; ++i) {
		g.deleteNode(i);
	}
	
	for (int i = -1; i > -500; --i) {
		g.addNode(i);
	}
	
	g.addEdge(1000,-1,2);
	g.addEdge(1000,-499,2);
	g.addEdge(1000,999,4);
	
	g.begin();
//	std::cout << g.value() << std::endl;
	g.next();
//	std::cout << g.value() << std::endl;
}

