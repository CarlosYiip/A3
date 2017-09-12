#include <random>
#include <vector>
#include <set>
#include <algorithm>

#include "Graph.h"

// the performance of this test heavily depends on the underlying data structure
// if sorting is happening during runtime then problems will occur.

// tests merge replace

int main() {
	
	unsigned int totalNumbers = 50;
	
	// use totalNumbers required as the seed for the random
	// number generator. 
	std::mt19937 mt(totalNumbers);
	std::uniform_int_distribution<unsigned int> dist(1, totalNumbers * 5);

	// make a graph
	gdwg::Graph<unsigned int,int> g;

	std::set<unsigned int> numSet;

	// insert random numbers into the sort object
	for (unsigned int i=0; i < totalNumbers * 2; ++i) {
		unsigned int num = dist(mt); 
		numSet.insert(num);
		g.addNode(num);
	}
	
	// iterate over the nodes to create a set of nodes. 
	std::vector<unsigned int> nodeValues;
	for (unsigned int n : numSet) {
		nodeValues.push_back(n);
	}
	
	// shuffle over the set
	std::shuffle(nodeValues.begin(), nodeValues.end(), std::default_random_engine(1));
	
	std::vector<unsigned int> nodesWithEdges;
	
	// insert some edges 
	for (unsigned int i = 0; i < nodeValues.size() - 4; i += 4) {
		g.addEdge(nodeValues[i], nodeValues[i+1], dist(mt));
		g.addEdge(nodeValues[i], nodeValues[i+2], dist(mt));
		g.addEdge(nodeValues[i], nodeValues[i+3], dist(mt));
		if (g.isNode(nodeValues[i])) nodesWithEdges.push_back(nodeValues[i]);
	}
	
	unsigned int toCheck = 0;
	
	// replace some random nodes.
	for (unsigned int i=0; i < (totalNumbers); ++i) {
		unsigned int oldVal = dist(mt); 
		unsigned int newVal = dist(mt); 
		try {
			if (oldVal == newVal) {
				continue; // don't merge with yourself, even though this should be fine!
			}
			if (toCheck == oldVal) {
				toCheck = 0;	// if the number toCheck is now about to be replaced. 
			}
			if (toCheck == 0 && std::find(nodeValues.begin(),nodeValues.end(),newVal) != nodeValues.end() && std::find(nodesWithEdges.begin(),nodesWithEdges.end(),oldVal) != nodesWithEdges.end()) {
				g.printEdges(oldVal);	// print the old edges before the replace. 
				g.printEdges(newVal);	// print the old edges before the replace. 
				toCheck = newVal;
				
				// need to sort out what now has edges in our collection. 
				nodesWithEdges.erase(std::remove(nodesWithEdges.begin(), nodesWithEdges.end(), oldVal), nodesWithEdges.end());
				nodesWithEdges.push_back(newVal);
			}
			g.mergeReplace(oldVal,newVal);
		} catch (...) {
			// silently continue.
		}
	}
	
	// print one of the edges. 
	g.printEdges(toCheck);
	
}

