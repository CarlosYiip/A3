#include "Graph.h"

// create a graph
// add 10000 -> 1 nodes
// delete 1 -> 5000 nodes
// add -5000 -> -1 nodes
// add edge -5000 to -1
// add edge -5000 to 5000
// print edges

int main() {
	
	gdwg::Graph<int,int> g;
	
	for (int i = 10000; i > 0; --i) {
		g.addNode(i);
	}
	
	for (int i = 0; i < 5000; ++i) {
		g.deleteNode(i);
	}
	
	for (int i = -1; i > -5000; --i) {
		g.addNode(i);
	}
	
	g.addEdge(-4999,-1,2);
	g.addEdge(-4999,10000,3);
	
	g.printEdges(-4999);
}

