#include "Graph.h"

int main() {

   gdwg::Graph<std::string, int> g1{};

   std::string s = "a";
   std::cout << g1.addNode(s) << '\n';
   std::cout << g1.addNode("a") << '\n';
   g1.helper();



    return 0;
}