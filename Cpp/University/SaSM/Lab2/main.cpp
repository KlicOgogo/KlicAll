#include <iostream>
#include "ddg.h"

int main() {
    const int SAMPLES = 1000;
    const double p = 0.4;
    auto b_sample = ddg::bernoulli(SAMPLES, p);
    auto g_sample = ddg::geometric(SAMPLES, p);
    const size_t m = 10;
    auto nb_sample = ddg::negative_binomial(SAMPLES, m, p);
    const size_t N = 100, D = 20, n = 40;
    auto hg_sample = ddg::hyperheometric(SAMPLES, n, D, N);
    std::vector<int> values = {1, 5, 76, 10};
    auto u_sample = ddg::uniform(SAMPLES, values);
    std::cout << ddg::pt::bernoulli(b_sample, p) << '\n';
    std::cout << ddg::pt::geometric(g_sample, p) << '\n';
    std::cout << ddg::pt::negative_binomial(nb_sample, p, m) << '\n';
    std::cout << ddg::pt::hyperheometric(hg_sample, n, D, N) << '\n';
    std::cout << ddg::pt::uniform(u_sample, values) << '\n';
    return 0;
}