#include <cmath>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace func {
double f(double x, double y) {
    return std::abs(x-y);
}
double psi_1(double y) {
    return -y*(y-1);
}
double psi_2(double y) {
    return -psi_1(y);
}
double psi_3(double x) {
    return std::abs(std::sin(M_PI*x));
}
double psi_4(double x) {
    return std::exp(x)*psi_3(x);
}
}
#endif // FUNCTIONS_H
