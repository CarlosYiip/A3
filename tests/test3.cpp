#include <random>
#include <vector>
#include <algorithm>
#include <sstream>

#include "Graph.h"

// the performance of this test heavily depends on the underlying data structure
// if sorting is happening during runtime then problems will occur.

// also relies on the iterator. 

int main() {
	
	unsigned int totalNumbers = 100;
	
	// use totalNumbers required as the seed for the random
	// number generator. 
	std::mt19937 mt(totalNumbers);
	std::uniform_int_distribution<unsigned int> dist(1, totalNumbers * 5);

	// make a graph
	gdwg::Graph<unsigned int,int> g;

	// insert random numbers into the sort object
	for (unsigned int i=0; i < totalNumbers; ++i) {
		g.addNode(dist(mt));
	}
	
	// delete some random nodes.
	for (unsigned int i=0; i < (totalNumbers / 2); ++i) {
		g.deleteNode(dist(mt));
	}
	
	// insert some more random numbers
	for (unsigned int i=0; i < totalNumbers; ++i) {
		g.addNode(dist(mt));
	}
	
	// We don't have iterators. So we iterate the node values
	// by using the output of printNodes(), for testing purposes.
        std::stringstream ss;

        //change the underlying buffer and save the old buffer
        auto old_buf = std::cout.rdbuf(ss.rdbuf()); 

	g.printNodes();

	std::cout.rdbuf(old_buf); //reset
	
	std::vector<unsigned int> nodeValues;
	unsigned int i;
	while (ss >> i) {
		nodeValues.push_back(i);
	}

	// END of ITERATION
	
	// shuffle over the set
	std::shuffle(nodeValues.begin(), nodeValues.end(), std::default_random_engine(1));
	
	// insert some edges 
	for (unsigned int i = 0; i < nodeValues.size() - 4; i += 4) {
		g.addEdge(nodeValues[i], nodeValues[i+1], dist(mt));
		g.addEdge(nodeValues[i], nodeValues[i+2], dist(mt));
		g.addEdge(nodeValues[i], nodeValues[i+3], dist(mt));
	}
	
	// print one of the edges. 
	g.printEdges(nodeValues[4]);
	
}

