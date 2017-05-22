#include "random_graph.h"

RandomGraph::RandomGraph(const RandomGraph &graph) : order(graph.order) {
    adj_lists.clear();
    adj_vectors.clear();
    adj_lists.resize(graph.order);
    adj_vectors.resize(graph.order);
    for (size_t i = 0; i < graph.order; i++) {
        adj_vectors[i].reserve(graph.order);
        for (size_t j = 0; j < graph.adj_vectors[i].size(); j++) {
            adj_lists[i].push_back(graph.adj_vectors[i][j]);
            adj_vectors[i].push_back(graph.adj_vectors[i][j]);
        }
    }
}


RandomGraph &RandomGraph::operator=(const RandomGraph &graph) {
    order = graph.order;
    adj_lists.clear();
    adj_vectors.clear();
    adj_lists.resize(graph.order);
    adj_vectors.resize(graph.order);
    for (size_t i = 0; i < graph.order; i++) {
        adj_vectors[i].reserve(graph.order);
        for (size_t j = 0; j < graph.adj_vectors[i].size(); j++) {
            adj_lists[i].push_back(graph.adj_vectors[i][j]);
            adj_vectors[i].push_back(graph.adj_vectors[i][j]);
        }
    }
    return *this;
}

RandomGraph::RandomGraph(const std::vector<std::vector<int> > &adj_vectors_, size_t order_) : order(order_) {
    adj_lists.clear();
    adj_vectors.clear();
    adj_lists.resize(order_);
    adj_vectors.resize(order_);
    for (size_t i = 0; i < order_; i++) {
        adj_vectors[i].reserve(order_);
        for (size_t j = 0; j < adj_vectors_[i].size(); j++) {
            adj_lists[i].push_back(adj_vectors_[i][j]);
            adj_vectors[i].push_back(adj_vectors_[i][j]);
        }
    }
}


void RandomGraph::generate(size_t order_, double probability) {
    adj_lists.clear();
    adj_vectors.clear();
    order = order_;
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    adj_lists.resize(order_);
    adj_vectors.resize(order_);
    for (int i = 0; i < order_; i++) {
        adj_vectors[i].reserve(order_);
    }
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < i; j++) {
            if (distribution(generator) < probability) {
                adj_lists[i].push_back(j);
                adj_lists[j].push_back(i);
                adj_vectors[i].push_back(j);
                adj_vectors[j].push_back(i);
            }
        }
    }
}

bool RandomGraph::connected() const {
    std::vector<int> visited(order);
    std::queue<int> q;
    size_t count = 0;
    q.push(0);
    count++;
    visited[0] = 1;
    while (!q.empty() && count != order) {
        int top = q.front();
        q.pop();
        for (auto it = adj_lists[top].begin(); it != adj_lists[top].end(); it++) {
            if (visited[*it] == 0) {
                visited[*it] = 1;
                q.push(*it);
                count++;
            }
        }
    }
    if (count == order)
        return true;
    else {
        return false;
    }
}

std::vector<std::list<int> > &RandomGraph::get_adj_lists() {
    return adj_lists;
}

std::vector<std::vector<int> > &RandomGraph::get_adj_vectors() {
    return adj_vectors;
}

size_t RandomGraph::get_order() const {
    return order;
}

void RandomGraph::print() const {
    for (size_t i = 0; i < adj_lists.size(); i++) {
        for (auto it = adj_lists[i].begin(); it != adj_lists[i].end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << '\n';
    }
}
