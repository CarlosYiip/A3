//
// Created by carlos Ye on 10/9/17.
//

#ifndef A3_GRAPH_H
#define A3_GRAPH_H

#include <list>
#include <memory>
#include <iostream>
#include <algorithm>


namespace gdwg {

    template <typename, typename> class Graph;
    template <typename N, typename E> class Graph {
    public:
        Graph() = default;

        Graph(const Graph&);

        Graph(Graph&&) = default;

        Graph& operator=(const Graph&);

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

        void printEdges(const N&) const;

        void begin() const;

        bool end() const;

        void next() const;

        const N& value() const;

    private:
        class Node {
            friend bool operator<(const Node &lhs, const Node &rhs) {
                if (lhs.get_out_degree() < rhs.get_out_degree()) {
                    return true;
                } else if (lhs.get_out_degree() == rhs.get_out_degree()) {
                    return lhs.get_data() < rhs.get_data();
                } else {
                    return false;
                }
            };

            friend bool operator==(const Node &rhs, const Node &lhs) {
                return rhs.get_data() == lhs.get_data();
            }

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

        private:
            std::shared_ptr<N> data_ptr;
            unsigned in_degree = 0u;
            unsigned out_degree = 0u;

        };

        class Edge {
            friend bool operator<(const Edge &rhs, const Edge &lhs) {
                if (rhs.get_weight() < lhs.get_weight()) {
                    return true;
                } else if (rhs.get_weight() == lhs.get_weight()) {
                    const std::shared_ptr<Node> rhs_dst_node_sp = rhs.get_src_wp().lock();
                    const std::shared_ptr<Node> lhs_dst_node_sp = lhs.get_src_wp().lock();
                    return rhs_dst_node_sp < lhs_dst_node_sp;
                } else {
                    return false;
                }
            };

            friend bool operator==(const Edge &rhs, const Edge &lhs) {
                return rhs.get_src_data() == lhs.get_src_data() &&
                       rhs.get_dst_data() == lhs.get_dst_data() &&
                       rhs.get_weight() == lhs.get_weight();
            };

        public:
            Edge(const std::shared_ptr<Node>&, const std::shared_ptr<Node>&, const E&);

            const N& get_src_data() const;

            const N& get_dst_data() const;

            const E& get_weight() const;

            void set_src_node(const std::shared_ptr<Node>&);

            void set_dst_node(const std::shared_ptr<Node>&);

            std::weak_ptr<Node>& get_src_wp();

            std::weak_ptr<Node>& get_dst_wp();

            const std::weak_ptr<Node>& get_src_wp() const;

            const std::weak_ptr<Node>& get_dst_wp() const;

        private:
            std::weak_ptr<Node> src_ptr;
            std::weak_ptr<Node> dst_ptr;
            E weight;
        };

        std::list<std::shared_ptr<Node>> nodes_sp;
        std::list<Edge> edges;

        mutable typename std::list<std::shared_ptr<Node>>::const_iterator const_iter;
    };

    #include "Graph.cpp"
};
#endif //A3_GRAPH_H
