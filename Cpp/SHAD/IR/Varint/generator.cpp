#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>

const int N = 10000;

int geometric(double p) {
        std::random_device device;
        std::default_random_engine gen(device());
        std::uniform_real_distribution<double> distr(0.0, 1.0);
        double a = distr(gen);
        return static_cast<unsigned int>(std::log(a) / std::log(1 - p)) + 1;
    }
    
void print_numbers(double p) {
    for (int i = 0; i < N; ++i) {
        std::cout << geometric(p) << '\n';
    }
}

int main() {
    double p;
    std::cin >> p;
    print_numbers(p);
    std::ofstream out("log.txt", std::ios::out | std::ios::app);
    out << 4 * N << ' ';
    out.close();
    return 0;
}
