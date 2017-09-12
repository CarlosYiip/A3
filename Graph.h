//
// Created by carlos Ye on 10/9/17.
//

#ifndef A3_GRAPH_H
#define A3_GRAPH_H

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>


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

        bool replace(const N&, const N&);

        void mergeReplace(const N&, const N&);

        void deleteNode(const N&) noexcept;

        void deleteEdge(const N&, const N&, const E&) noexcept;

        void clear() noexcept;

        bool isNode(const N&) const;

        bool isConnected(const N&, const N&) const;

        void printNodes() const;

        void printEdges() const;


    private:
        class Node {
        public:
            Node(const N&);

            const N& get_data() const;

            void set_data(const N&);

            unsigned get_in_degree() const;

            unsigned get_out_degree() const;

            void inc_in_degree();

            void inc_out_degree();

            void dec_in_degree();

            void dec_out_degree();

            void set_in_degree(unsigned);

            void set_out_degree(unsigned);

        private:
            std::unique_ptr<N> data_ptr;
            unsigned in_degree = 0u;
            unsigned out_degree = 0u;

        };

        class Edge {
        public:
            Edge(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&, const E&);

            const N& get_src_data() const;

            const N& get_dst_data() const;
            
            const E& get_weight() const;

            const std::weak_ptr<Node>& get_src_ptr() const;

            const std::weak_ptr<Node>& get_dst_ptr() const;

            void set_src_node(const std::shared_ptr<Node>&);
            
            void set_dst_node(const std::shared_ptr<Node>&);
        private:
            std::weak_ptr<Node> src_ptr;
            std::weak_ptr<Node> dst_ptr;
            E weight;

        };

        std::vector<std::shared_ptr<Node>> nodes_sp;
        std::vector<Edge> edges;
    };


    #include "Graph.tem"
};
#endif //A3_GRAPH_H
