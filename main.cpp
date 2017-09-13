#include "Graph.h"

int main() {
    gdwg::Graph<std::string, int> g1{};
    std::string s = "a";
    g1.addNode(s);
    g1.addNode("zzz");
    g1.addNode("b");
    g1.addNode("a");
    g1.addNode("cd");
//    g1.addEdge("a", "zzz", 30);
//    g1.addEdge("a", "b", 10);
//    g1.addEdge("cd", "ab", 10);
//
//    g1.replace("a", "!!");
//    g1.mergeReplace("!!", "zzz");
//    g1.deleteNode("b");
//    g1.deleteEdge("a", "c");
//
    g1.printNodes();
//    g1.printEdges("zzz");
//    g1.printEdges("cd");


//    std::vector<int> v {1,2,3,4,5,6};
//
//    auto it = std::lower_bound(v.begin(),v.end(),3);
//
//    v.insert(it, 3);
//
//
//    for (auto i : v)
//        std::cout << i << '\n';

    return 0;
}