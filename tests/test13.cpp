#include "Graph.h"

// edge iterators test

int main() {
	
	gdwg::Graph<std::shared_ptr<std::string>,int> g;
	
	auto n1 = std::make_shared<std::string>("a");
	auto n2 = std::make_shared<std::string>("b");
	auto n3 = std::make_shared<std::string>("c");
	auto n4 = std::make_shared<std::string>("c");
	g.addNode(n1);
	g.addNode(n2);
	g.addNode(n3);
	g.addNode(n4);
	
	std::cout << std::boolalpha << g.isNode(n3) << " " << g.isNode(n4) << " " << g.isNode(std::make_shared<std::string>("c")) << std::endl;
	
	g.deleteNode(n1);
	g.deleteNode(n4);
	g.deleteNode(n3);
	
	for (auto n : g) {
		std::cout << *n << std::endl;
	}
	
	gdwg::Graph<std::string,int> g2;
	g2.addNode("d");
	g2.addNode("e");
	g2.addNode("f");
	g2.addNode("g");
	
	g2.addEdge("e","f",1);
	g2.addEdge("e","d",2);
	g2.addEdge("e","g",2);
	g2.addEdge("e","g",-3);
	
	g2.printEdges("e");

	g2.addEdge("d","f",1);
	g2.addEdge("d","g",2);
	g2.addEdge("d","g",-3);
	g2.addEdge("e","d",-3);
	
	// trying iterator over edges attached to this node. 
	for (auto edge = g2.edgeIteratorBegin("d"); edge != g2.edgeIteratorEnd(); ++edge) {
		std::cout << (*edge).first << " " << (*edge).second << std::endl;
	}
	
	std::cout << "trying -> overload on iterator" << std::endl;
	for (auto edge = g2.edgeIteratorBegin("d"); edge != g2.edgeIteratorEnd(); ++edge) {
		std::cout << edge->first << " " << edge->second << std::endl;
	}
}

