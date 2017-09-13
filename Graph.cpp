
/************************************************* Graph **************************************************/
template <typename N, typename E>
Graph<N, E>::Graph(const Graph<N, E> &other) {
	for (auto it = other.nodes_sp.cbegin(); it != other.nodes_sp.cend(); ++it) {
		Node new_node {**it};
		nodes_sp.emplace_back(std::make_shared<Node>(new_node));
	}

	for (auto it = other.edges.cbegin(); it != other.edges.cend(); ++it) {
		auto src_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(),
								   [&] (const std::shared_ptr<Node>& sp) {
			return sp->get_data() == it->get_src_data();
								   });


		auto dst_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(),
								   [&] (const std::shared_ptr<Node>& sp) {
									   return sp->get_data() == it->get_dst_data();
								   });

		Edge new_edge {*src_it, *dst_it, it->get_weight()};
		edges.emplace_back(new_edge);
	}
};

template <typename N, typename E>
Graph<N, E>& Graph<N, E>::operator=(const Graph& other) {
	if (this != &other) {
		nodes_sp.clear();
		edges.clear();

		for (auto it = other.nodes_sp.cbegin(); it != other.nodes_sp.cend(); ++it) {
			Node new_node {**it};
			nodes_sp.emplace_back(std::make_shared<Node>(new_node));
		}

		for (auto it = other.edges.cbegin(); it != other.edges.cend(); ++it) {
			auto src_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(),
									   [&] (const std::shared_ptr<Node>& sp) {
										   return sp->get_data() == it->get_src_data();
									   });


			auto dst_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(),
									   [&] (const std::shared_ptr<Node>& sp) {
										   return sp->get_data() == it->get_dst_data();
									   });

			Edge new_edge {*src_it, *dst_it, it->get_weight()};
			edges.emplace_back(new_edge);
		}
	}
	return *this;
};


template <typename N, typename E>
bool Graph<N, E>::addNode(const N &val) {
    if (isNode(val))
    	return false;

    std::shared_ptr<Node> new_sp = std::make_shared<Node>(Node {val});
    auto it = std::lower_bound(nodes_sp.cbegin(), nodes_sp.cend(), new_sp,
                               [](const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) {
                                   return *lhs < *rhs;
                               });

    nodes_sp.insert(it, new_sp);

    return true;
}

template <typename N, typename E>
bool Graph<N, E>::addEdge(const N &src, const N &dst, const E &w) {
	auto edge_it = std::find_if(edges.cbegin(), edges.cend(), [&] (const Edge &edge) {
		return edge.get_src_data() == src &&
               edge.get_dst_data() == dst &&
               edge.get_weight() == w;
	});

	if (edge_it != edges.cend())
		return false;

    auto src_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node> &sp) {
        return sp->get_data() == src;
    });

    auto dst_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node> &sp) {
        return sp->get_data() == dst;
    });

    if (src_it == nodes_sp.cend())
        throw std::runtime_error("src not in graph");

    if (dst_it == nodes_sp.cend())
        throw std::runtime_error("dst not in graph");

    (*src_it)->inc_out_degree();
    (*dst_it)->inc_in_degree();
    Edge new_edge{*src_it, *dst_it, w};

    auto it = std::lower_bound(edges.cbegin(), edges.cend(), new_edge);
    edges.insert(it, new_edge);

	nodes_sp.sort([] (const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) {
		return *lhs < *rhs;
	});

    return true;
};

template <typename N, typename E>
bool Graph<N, E>::replace(const N &old_data, const N &new_data) {
	auto old_it = std::find_if(nodes_sp.begin(), nodes_sp.end(), [&] (std::shared_ptr<Node> &sp) {
		return sp->get_data() == old_data;
	});

	if (old_it == nodes_sp.end())
		throw std::runtime_error("old node not in the graph");

	auto new_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node> &sp) {
		return sp->get_data() == new_data;
	});

	if (new_it != nodes_sp.cend())
		return false;

	(*old_it)->set_data(new_data);

	nodes_sp.sort([] (const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) {
		return *lhs < *rhs;
	});


	return true;
}

template <typename N, typename E>
void Graph<N, E>::mergeReplace(const N &old_data, const N &new_data) {
	auto old_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node> &sp) {
		return sp->get_data() == old_data;
	});

	auto new_it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node> &sp) {
		return sp->get_data() == new_data;
	});

	if (old_it == nodes_sp.end())
		throw std::runtime_error(std::to_string(old_data) + " is not in the graph");

	if (new_it == nodes_sp.end())
		throw std::runtime_error(std::to_string(new_data) + " is not in the graph");


	std::for_each(edges.begin(), edges.end(), [&] (Edge &edge){
		if (edge.get_src_data() == old_data) {
            edge.set_src_node(*new_it);
            (*new_it)->inc_out_degree();
        }
        if (edge.get_dst_data() == old_data) {
            edge.set_dst_node(*new_it);
            (*new_it)->inc_in_degree();
        }
	});

    edges.sort();

    edges.unique();

	nodes_sp.erase(old_it);
}


template <typename N, typename E>
void Graph<N, E>::deleteNode(const N& d) noexcept {
	auto it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node>& sp) {
		return sp->get_data() == d;
	});

	if (it != nodes_sp.end()) {
        nodes_sp.erase(it);

        edges.remove_if([](Edge &edge) {
            std::shared_ptr <Node> src_sp = edge.get_src_wp().lock();
            std::shared_ptr <Node> dst_sp = edge.get_dst_wp().lock();
            return (!src_sp || !dst_sp);
        });
    }
}

template <typename N, typename E>
void Graph<N, E>::deleteEdge(const N& src, const N& dst, const E& w) noexcept {
	auto it = std::find_if(edges.begin(), edges.end(), [&] (const Edge& edge) {
		return edge.get_src_data() == src &&
			   edge.get_dst_data() == dst &&
			   edge.get_weight() == w;
	});
	if (it != edges.end()) {

        std::shared_ptr<Node> src_ptr = it->get_src_wp().lock();
        if (src_ptr)
            src_ptr->dec_out_degree();

        std::shared_ptr<Node> dst_ptr = it->get_dst_wp().lock();
        if (dst_ptr)
            dst_ptr->dec_in_degree();

		edges.erase(it);
	}
}


template <typename N, typename E>
void Graph<N, E>::clear() noexcept {
	nodes_sp.clear();
	edges.clear();
}

template <typename N, typename E>
bool Graph<N, E>::isNode(const N& val) const {
	auto it = std::find_if(nodes_sp.cbegin(), nodes_sp.cend(), [&] (const std::shared_ptr<Node> &sp) {
		return sp->get_data() == val;
	});

	return it != nodes_sp.cend();
}

template <typename N, typename E>
bool Graph<N, E>::isConnected(const N &src, const N &dst) const {
	if (!isNode(src))
		throw std::runtime_error("src is not in the graph");
	if (!isNode(dst))
		throw std::runtime_error("dst is not in the graph");

	auto it = std::find_if(edges.cbegin(), edges.cend(), [&] (const Edge& edge) {
		bool b1 = edge.get_src_data() == src;
		bool b2 = edge.get_dst_data() == dst;
		return b1 && b2;
	});

	return it != edges.cend();
}

template <typename N, typename E>
void Graph<N, E>::printNodes() const {
    std::for_each(nodes_sp.cbegin(), nodes_sp.cend(), [] (const std::shared_ptr<Node>& sp) {
		std::cout << sp->get_data() << '\n';
//        std::cout << sp->get_data() << " in: " << sp->get_in_degree() << " out: " << sp->get_out_degree() << '\n';
    });
};

template <typename N, typename E>
void Graph<N, E>::printEdges(const N& val) const {
    if (!isNode(val))
        throw std::runtime_error("this node is not in the graph");

    std::cout << "Edges attached to Node " << val << '\n';
    bool has_dst_nodes = false;

    std::for_each(edges.cbegin(), edges.cend(), [&] (const Edge &edge) {
        if (edge.get_src_data() == val) {
            has_dst_nodes = true;
            std::cout << edge.get_dst_data() << " " << edge.get_weight() << '\n';
        }
    });

    if (!has_dst_nodes)
        std::cout << "(null)" << '\n';
};

/************************************************* Node **************************************************/

template <typename N, typename E>
Graph<N, E>::Node::Node(const N &val) : data_ptr{std::make_shared<N>(val)} {};

 template <typename N, typename E>
 Graph<N, E>::Node::Node(const typename Graph<N, E>::Node& other) : in_degree{other.in_degree}, out_degree{other.out_degree} {
	 N new_data = other.get_data();
	 data_ptr = std::make_shared<N>(new_data);
 }

 template <typename N, typename E>
 Graph<N, E>::Node::Node(typename Graph<N, E>::Node&& other) :
		 in_degree{std::move(other.in_degree)}, out_degree{std::move(other.out_degree)},
		 data_ptr{std::move(other.data_ptr)} {}

 template <typename N, typename E>
 typename Graph<N, E>::Node& Graph<N, E>::Node::operator=(const typename Graph<N, E>::Node& other) {
	 if (this != &other) {
		 in_degree = other.in_degree;
		 out_degree = other.out_degree;
		 data_ptr = std::make_shared<N>(other.get_data());
	 }
 };

 template <typename N, typename E>
 typename Graph<N, E>::Node& Graph<N, E>::Node::operator=(typename Graph<N, E>::Node&& other) {
	 if (this != &other) {
		 in_degree = std::move(other.in_degree);
		 out_degree = std::move(other.out_degree);
		 data_ptr = std::move(other.data_ptr);
	 }
 };

template <typename N, typename E>
const N &Graph<N, E>::Node::get_data() const { return *data_ptr; };

template <typename N, typename E>
void Graph<N, E>::Node::set_data(const N &new_data) { data_ptr = std::make_shared<N>(new_data); };

template <typename N, typename E>
unsigned Graph<N, E>::Node::get_in_degree() const { return in_degree; };

template <typename N, typename E>
unsigned Graph<N, E>::Node::get_out_degree() const { return out_degree; };

template <typename N, typename E>
void Graph<N, E>::Node::inc_in_degree() { ++in_degree; };

template <typename N, typename E>
void Graph<N, E>::Node::inc_out_degree() { ++out_degree; };

template <typename N, typename E>
void Graph<N, E>::Node::dec_in_degree() { --in_degree; };

template <typename N, typename E>
void Graph<N, E>::Node::dec_out_degree() { --out_degree; };


/************************************************* Edge **************************************************/

template <typename N, typename E>
Graph<N, E>::Edge::Edge(const std::shared_ptr<Node> &src, const std::shared_ptr<Node> &dst, const E &w) : src_ptr{src}, dst_ptr{dst}, weight{w} {}

template <typename N, typename E>
const N& Graph<N, E>::Edge::get_src_data() const { return src_ptr.lock()->get_data(); }

template <typename N, typename E>
const N& Graph<N, E>::Edge::get_dst_data() const { return dst_ptr.lock()->get_data(); }

template <typename N, typename E>
const E& Graph<N, E>::Edge::get_weight() const {return weight; }

template <typename N, typename E>
void Graph<N, E>::Edge::set_src_node(const std::shared_ptr<Node> &src) { src_ptr = src; }

template <typename N, typename E>
void Graph<N, E>::Edge::set_dst_node(const std::shared_ptr<Node> &dst) { dst_ptr = dst; }

template <typename N, typename E>
std::weak_ptr<typename Graph<N, E>::Node>& Graph<N, E>::Edge::get_src_wp() { return src_ptr; }

template <typename N, typename E>
std::weak_ptr<typename Graph<N, E>::Node>& Graph<N, E>::Edge::get_dst_wp() { return dst_ptr; }


 template <typename N, typename E>
 const std::weak_ptr<typename Graph<N, E>::Node>& Graph<N, E>::Edge::get_src_wp() const { return src_ptr; }

 template <typename N, typename E>
 const std::weak_ptr<typename Graph<N, E>::Node>& Graph<N, E>::Edge::get_dst_wp() const { return dst_ptr; }









