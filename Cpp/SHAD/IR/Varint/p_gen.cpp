#include <random>
#include <cmath>
#include <fstream>
#include <iostream>

int main() {
    std::random_device device;
    std::default_random_engine gen(device());
    std::uniform_real_distribution<double> distr(0.0, 1.0);
    double p = std::exp(-10 * distr(gen));
    std::ofstream out("log.txt", std::ios::out | std::ios::app);
    out << p << ' ';
    out.close();
    std::cout << p;
    return 0;
}
