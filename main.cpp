#include "Graph.h"

int main() {
    gdwg::Graph<std::string, int> g1{};
    std::string s = "a";
    std::cout << g1.addNode(s) << '\n';
    std::cout << g1.addNode("b") << '\n';
    std::cout << g1.addEdge("a", "b", 1) << '\n';
    std::cout << g1.addEdge("a", "b", 1) << '\n';

    g1.mergeReplace("a", "b");
    std::cout << g1.addNode("b") << '\n';

    g1.deleteNode("a");

    return 0;
}