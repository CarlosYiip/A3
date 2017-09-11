//
// Created by carlos Ye on 10/9/17.
//

#ifndef A3_GRAPH_H
#define A3_GRAPH_H

#include <vector>
#include <memory>
#include <iostream>

namespace gdwg {

    template <typename, typename> class Graph;
    template <typename N, typename E> class Graph {
    public:
        Graph() = default;

        Graph(const Graph&) = default;

        Graph(Graph&&) = default;

        Graph& operator=(const Graph&) = default;

        Graph& operator=(Graph&&) = default;

        bool addNode(const N&);

        bool addEdge(const N&, const N&, const E&);


    private:

        bool node_existed(const N&) const;
        bool edge_existed(const N&, const N&, const E&) const;

        class Node {
        public:
            Node(const N&);

            const N& get_data() const;

        private:
            std::shared_ptr<N> data_ptr;
            unsigned in_degree = 0u;
            unsigned out_degree = 0u;

        };


        class Edge {
        public:
            Edge(const N&, const N&, const E&);
            const N& get_src_data() const;
            const N& get_dst_data() const;
            const E& get_weight() const;
        private:
            std::weak_ptr<Node> src_ptr;
            std::weak_ptr<Node> dst_ptr;
            E weight;

        };


        std::vector<std::share_ptr<Node>> nodes;
        std::vector<std::weak_ptr<Edge>> edges;
    };
    #include "Graph.tem"
}

#endif //A3_GRAPH_H
