#include <limits>
#include <cmath>

#include "Graph.h"

// move semantics

// create two graphs
// keep calling std::swap
// keep deleting from one
// keep adding an edge in the other. 

int main() {
	
	gdwg::Graph<long long, long long> g1;
	
	// create some nodes
	int counter = 0;
	for (long i = 2; counter < 50000; i *= i) {
		g1.addNode(i);
		++counter;
	}
	
	// create some edges
	counter = 0;
	for (long i = 4; counter < 50000; i *= i) {
		g1.addEdge(i,i*i,i);
		g1.addEdge(i,std::sqrt(i),i);
		++counter;
	}
	
	// copy construct a graph
	gdwg::Graph<long long, long long> g2 = g1;
	
	// play with std::move
	counter = 0;
	for (long i = 2; counter < 50000; i *= i) {
		if (i % 8) g1.deleteNode(i);
		std::swap(g1,g2);	// swap always
		++counter;
	}
	
	
	g1.printEdges(4);
	g2.printEdges(16);
}

