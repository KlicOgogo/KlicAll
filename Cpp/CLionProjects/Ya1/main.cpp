#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    double sum = 0;
    for (int i = 0; i < n; ++i ) {
        std::cin >> a[i] >> b[i];
        c[i] = a[i] * b[i];
        sum += c[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cout << std::setprecision(10) << c[i] / sum << '\n';
    }
    return 0;
}