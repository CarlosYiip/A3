//#include "Graph.h"
#include <memory>

int main() {

//    gdwg::Graph<std::string, int> g1{};
//
//    std::string s = "a";
//    g1.addNode(s);
//    g1.addNode("b");
//    g1.addEdge("a", "b", 1);

    std::shared_ptr<int> sp = std::make_shared<int>(1);
    std::weak_ptr<int> wp ;


    return 0;
}