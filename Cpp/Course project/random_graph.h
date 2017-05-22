#ifndef RANDOM_GRAPH_H
#define RANDOM_GRAPH_H

#include <vector>
#include <list>
#include <random>
#include <queue>
#include <iostream>

class RandomGraph {
public:
    RandomGraph() = default;

    RandomGraph(const RandomGraph &graph);
    RandomGraph &operator=(const RandomGraph &graph);

    RandomGraph(const std::vector<std::vector<int> > &adj_vectors_, size_t order_);

    void generate(size_t order_, double probability);

    bool connected() const;

    std::vector<std::list<int> > &get_adj_lists();

    std::vector<std::vector<int> > &get_adj_vectors();

    size_t get_order() const;

    void print() const;

private:
    std::vector<std::list<int> > adj_lists;
    std::vector<std::vector<int> > adj_vectors;
    size_t order;
};

#endif
