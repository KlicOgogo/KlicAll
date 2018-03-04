#include <cmath>
#include <vector>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace func {
/* mine
double k(double x) {
    return std::pow(std::cos(x), 2);
}
double q(double x) {
    return std::sin(2*x);
}
double f(double x) {
    return x*std::sin(2*x);
}
*/
double k(double x) {
    return 4-x*x;
}
double q(double x) {
    return x*x;
}
double f(double x) {
    return 4*std::cos(x)-2*x*std::sin(x);
}
class phi {
public:
    phi(double x, size_t n) {
        functions.resize(n+1);
        derivatives.resize(n+1);
        functions[0] = -0.177239203*x + 0.291043187;
        derivatives[0] = -0.177239203;
        for (size_t i = 1; i < n+1; i++) {
            functions[i] = std::pow(x, i+1)*std::pow(x-1, 2);
            derivatives[i] = (i+1)*std::pow(x, i)*std::pow(x-1, 2) + 2*(x-1)*std::pow(x, i+1);
        }
    }
    double getF(size_t i) {
        return functions[i];
    }
    double getD(size_t i) {
        return derivatives[i];
    }
private:
    std::vector<double> functions;
    std::vector<double> derivatives;
};

}
#endif

