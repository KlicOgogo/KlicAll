#include <iostream>
#include "mcm.h"

int main() {
    std::cout << "1D integral:\n";
    //std::cout << mcm::count_1D_integral(100000) << '\n';
    std::cout << "2D integral:\n";
    //std::cout << mcm::count_2D_integral(100000) << '\n';
    Matrix A = {{0.7, 0.1},
                {0.5, -0.1}};
    Vector f = {-3, 0.2};
    std::cout << "Linear system's solution:" << '\n';
    auto v = mcm::solve_linear_system(A, f, 20, 5000);
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << '\n';
    }
    return 0;
}
