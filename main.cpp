#include "Graph.h"

int main() {
    gdwg::Graph<std::string, int> g1{};
    std::string s = "a";
    std::cout << g1.addNode(s) << '\n';
    std::cout << g1.addNode("b") << '\n';
    std::cout << g1.addEdge("a", "b", 1) << '\n';
    std::cout << g1.addEdge("a", "b", 1) << '\n';
    std::cout << g1.addEdge("a", "c", 1) << '\n';




    return 0;
}