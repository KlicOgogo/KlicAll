#include <iostream>
#include "cdg.h"

int main() {
    const size_t N = 1000;
    auto uniform_sample = cdg::uniform(N, 4, 10);
    auto normal_sample = cdg::normal(N, 1, 4);
    auto normal_bm_sample = cdg::normal_bm(N, 1, 4);
    auto cauchy_sample = cdg::cauchy(N, 2, 10);
    auto chi_squared_sample = cdg::chi_squared(N, 4);
    auto logistic_sample = cdg::logistic(N, 2, 4);
    auto student_sample = cdg::student(N, 6);
    std::cout << "Uniform distribution Kolmogorov's test statistic:\n";
    std::cout << cdg::kt::uniform(uniform_sample, 4, 10) << '\n';
    std::cout << "Normal distribution Kolmogorov's test statistic:\n";
    std::cout << cdg::kt::normal(normal_sample, 1, 4) << '\n';
    std::cout << "Normal (Box-Muller) distribution Kolmogorov's test statistic:\n";
    std::cout << cdg::kt::normal(normal_bm_sample, 1, 4) << '\n';
    std::cout << "Cauchy's distribution Kolmogorov's test statistic:\n";
    std::cout << cdg::kt::cauchy(cauchy_sample, 2, 10) << '\n';
    std::cout << "Chi-squared distribution Kolmogorov's test statistic:\n";
    std::cout << cdg::kt::chi_squared(chi_squared_sample, 4) << '\n';
    std::cout << "Logistic distribution Kolmogorov's test statistic:\n";
    std::cout << cdg::kt::logistic(logistic_sample, 2, 4);
    return 0;
}