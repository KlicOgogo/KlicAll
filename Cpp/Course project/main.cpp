#include <iostream>
#include "random_graph.h"
#include "delivery_algorithms.h"

int main() {
    const int ORDER = 100;
    const int NUMBER_OF_TESTS = 20;
    const double PROBABILITY = 0.1;
    std::vector<std::vector<int> > result_of_alg(5, std::vector<int>(NUMBER_OF_TESTS));
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        RandomGraph graph;
        graph.generate(ORDER, PROBABILITY);
        DeliveryAlgorithms alg(graph, 0);
        result_of_alg[0][i] = alg.const_random(5);
        result_of_alg[1][i] = alg.random();
        result_of_alg[2][i] = alg.first();
        result_of_alg[3][i] = alg.max_degree();
        result_of_alg[4][i] = alg.min_degree_in_delivered();
    }
    for (int i = 0; i < result_of_alg.size(); i++) {
        for (int j = 0; j < result_of_alg[i].size(); j++) {
            std::cout << result_of_alg[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}