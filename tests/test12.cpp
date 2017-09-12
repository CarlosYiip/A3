#include "Graph.h"

// move over yourself. 

int main() {
	
	gdwg::Graph<float,int> g;
	
	g.addNode(3.14);
	g.addNode(4.2);
	g.addEdge(3.14,4.2,6);
	
	g = std::move(g);
	
	g.addNode(10.14);
	g.printEdges(10.14);
	
}

