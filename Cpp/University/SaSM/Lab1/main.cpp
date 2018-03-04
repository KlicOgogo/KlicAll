#include <iostream>
#include "brvg.h"

void print_tests_result(const std::vector<double> &sample, const std::string &method_name) {
    std::cout << method_name << '\n';
    std::cout << "moments criterion: ";
    auto stat = brvg::pc::moments(sample);
    if (stat.first < 1.36 && stat.second < 1.36) {
        std::cout << "accepted\n";
    } else {
        std::cout << "failed\n";
    }
    std::cout << "Kolmogorov's criterion: ";
    if (brvg::pc::kolmogorov(sample) < 1.36) {
        std::cout << "accepted\n";
    } else {
        std::cout << "failed\n";
    }
    std::cout << "Pearson's criterion: ";
    if (brvg::pc::pearson(sample, 10) < 16.92) {
        std::cout << "accepted\n";
    } else {
        std::cout << "failed\n";
    }
    std::cout << '\n';
}

int main() {
    int first_value = 5;
    int beta = 5;
    size_t n_sample = 1000;
    auto lc_sample = brvg::lc(first_value, beta, n_sample);
    auto sr_sample = brvg::sr(n_sample);
    auto mm_sample = brvg::mm_sr_based(501, n_sample);
    print_tests_result(lc_sample, "linear congruental");
    print_tests_result(sr_sample, "standard random");
    print_tests_result(mm_sample, "MacLaren-Marsaglia");
    return 0;
}