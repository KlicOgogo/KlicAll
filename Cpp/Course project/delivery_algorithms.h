#include "random_graph.h"
#include <vector>
#include <list>
#include <random>
#include <unordered_set>
#include <cassert>
#include <algorithm>

#ifndef DELIVERY_ALGORITHMS_H
#define DELIVERY_ALGORITHMS_H

class DeliveryAlgorithms {
public:
    DeliveryAlgorithms() = default;

    DeliveryAlgorithms(const RandomGraph &graph_, int terminal_) :
            terminal(terminal_), order(graph_.get_order()) {
        if (graph_.connected()) {
            graph = graph_;
        } else {
            throw std::runtime_error("Graph is not connected!");
        }
    }

    int const_random(int attempts_count) {
        if (attempts_count <= 0) {
            throw std::runtime_error("Count of attempts is not positive.");
        }
        std::vector<int> delivered;
        delivered.reserve(order);
        std::vector<bool> is_delivered(order);
        delivered.push_back(terminal);
        is_delivered[terminal] = true;
        std::random_device device;
        std::default_random_engine generator(device());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        int steps_count = 0;
        while (delivered.size() < order) {
            std::vector<int> temp;
            temp.reserve(order);
            for (size_t i = 0; i < delivered.size(); i++) {
                for (int t = 0; t < attempts_count; t++) {
                    double generated = distribution(generator);
                    int index_to_deliver = (int) (generated * graph.get_adj_vectors()[delivered[i]].size());
                    int to_deliver = graph.get_adj_vectors()[delivered[i]][index_to_deliver];
                    if (!is_delivered[to_deliver]) {
                        is_delivered[to_deliver] = true;
                        temp.push_back(to_deliver);
                        break;
                    }
                }
            }
            for (size_t i = 0; i < temp.size(); i++) {
                delivered.push_back(temp[i]);
            }
            steps_count++;
            if (steps_count >= (int) order) {
                throw std::runtime_error("Algorithm failed.");
            }
        }
        return steps_count;
    }

    int random() {
        std::vector<int> delivered;
        delivered.reserve(order);
        std::vector<bool> is_delivered(order);
        delivered.push_back(terminal);
        is_delivered[terminal] = true;
        std::random_device device;
        std::default_random_engine generator(device());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        int steps_count = 0;
        std::vector<std::vector<int> > not_delivered(order);
        for (size_t i = 0; i < order; i++) {
            not_delivered[i].reserve(graph.get_adj_vectors()[i].size());
            for (size_t j = 0; j < graph.get_adj_vectors()[i].size(); j++) {
                if (graph.get_adj_vectors()[i][j] != terminal)
                    not_delivered[i].push_back(graph.get_adj_vectors()[i][j]);
            }
        }
        while (delivered.size() < order) {
            std::vector<int> temp;
            temp.reserve(order);
            for (size_t i = 0; i < delivered.size(); i++) {
                double generated = distribution(generator);
                if (not_delivered[delivered[i]].size() > 0) {
                    int index_to_deliver = (int) (generated * not_delivered[delivered[i]].size());
                    int to_deliver = not_delivered[delivered[i]][index_to_deliver];
                    is_delivered[to_deliver] = true;
                    temp.push_back(to_deliver);
                    for (size_t j = 0; j < not_delivered.size(); j++) {
                        auto iter = std::lower_bound(not_delivered[j].begin(),
                                                     not_delivered[j].end(), to_deliver);
                        if (iter != not_delivered[j].end() && *iter == to_deliver) {
                            not_delivered[j].erase(iter);
                        }
                    }
                }
            }
            for (size_t i = 0; i < temp.size(); i++) {
                delivered.push_back(temp[i]);
            }
            steps_count++;
        }
        return steps_count;
    }

    int first() {
        std::vector<std::list<int>::iterator> list_iterators(order);
        for (size_t i = 0; i < order; i++) {
            list_iterators[i] = graph.get_adj_lists()[i].begin();
        }
        std::vector<int> delivered;
        delivered.reserve(order);
        delivered.push_back(terminal);
        std::vector<bool> is_delivered(order);
        is_delivered[terminal] = true;
        int steps_count = 0;
        while (delivered.size() < order) {
            std::vector<int> temp;
            temp.reserve(order);
            for (size_t i = 0; i < delivered.size(); i++) {
                int count = 0;
                for (auto it = list_iterators[delivered[i]]; it != graph.get_adj_lists()[delivered[i]].end(); it++) {
                    if (!is_delivered[*it]) {
                        is_delivered[*it] = true;
                        temp.push_back(*it);
                        list_iterators[delivered[i]] = ++it;
                        count++;
                        break;
                    }
                }
                if (count == 0) {
                    list_iterators[delivered[i]] = graph.get_adj_lists()[delivered[i]].end();
                }
            }
            for (size_t i = 0; i < temp.size(); i++) {
                delivered.push_back(temp[i]);
            }
            steps_count++;
        }
        return steps_count;
    }

    int max_degree() {
        std::vector<int> delivered;
        delivered.reserve(order);
        std::vector<bool> is_delivered(order);
        delivered.push_back(terminal);
        is_delivered[terminal] = true;
        int steps_count = 0;
        std::vector<size_t> degrees_in_not_delivered(order);
        for (size_t i = 0; i < order; i++) {
            degrees_in_not_delivered[i] = graph.get_adj_lists()[i].size();
        }
        for (size_t i = 0; i < graph.get_adj_vectors()[terminal].size(); i++) {
            degrees_in_not_delivered[graph.get_adj_vectors()[terminal][i]]--;
        }
        while (delivered.size() < order) {
            std::vector<int> temp;
            temp.reserve(order);
            for (size_t i = 0; i < delivered.size(); i++) {
                int best_vertice = -1;
                size_t max_degree = 0;
                for (auto it = graph.get_adj_lists()[delivered[i]].begin();
                     it != graph.get_adj_lists()[delivered[i]].end(); it++) {
                    if (!is_delivered[*it] && degrees_in_not_delivered[*it] >= max_degree) {
                        best_vertice = *it;
                        max_degree = degrees_in_not_delivered[*it];
                    }
                }
                if (best_vertice != -1) {
                    temp.push_back(best_vertice);
                    is_delivered[best_vertice] = true;
                    for (auto it = graph.get_adj_lists()[best_vertice].begin();
                         it != graph.get_adj_lists()[best_vertice].end(); it++) {
                        degrees_in_not_delivered[*it]--;
                    }
                }
            }
            for (size_t i = 0; i < temp.size(); i++) {
                delivered.push_back(temp[i]);
            }
            steps_count++;
        }
        return steps_count;
    }

    int min_degree_in_delivered() {
        std::vector<int> delivered;
        delivered.reserve(order);
        std::vector<bool> is_delivered(order);
        delivered.push_back(terminal);
        is_delivered[terminal] = true;
        std::vector<int> degrees_in_delivered(order);
        for (size_t i = 0; i < graph.get_adj_vectors()[terminal].size(); i++) {
            degrees_in_delivered[graph.get_adj_vectors()[terminal][i]]++;
        }
        int steps_count = 0;
        while (delivered.size() < order) {
            std::vector<int> temp;
            temp.reserve(order);
            for (size_t i = 0; i < delivered.size(); i++) {
                int best_vertice = -1;
                int min_degree = order;
                for (auto iter = graph.get_adj_lists()[delivered[i]].begin();
                     iter != graph.get_adj_lists()[delivered[i]].end(); iter++) {
                    if (!is_delivered[*iter] && degrees_in_delivered[*iter] < min_degree) {
                        best_vertice = *iter;
                        min_degree = degrees_in_delivered[*iter];
                    }
                }
                if (best_vertice != -1) {
                    is_delivered[best_vertice] = true;
                    temp.push_back(best_vertice);
                }
            }
            for (size_t i = 0; i < temp.size(); i++) {
                delivered.push_back(temp[i]);
                for (auto iter = graph.get_adj_lists()[temp[i]].begin();
                     iter != graph.get_adj_lists()[temp[i]].end(); iter++) {
                    degrees_in_delivered[*iter]++;
                }
            }
            steps_count++;
        }
        return steps_count;
    }

private:
    RandomGraph graph;
    int terminal;
    size_t order;
};

#endif
