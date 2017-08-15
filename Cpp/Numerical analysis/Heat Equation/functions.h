#include <cmath>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace func {
double f(double x, double t) {
    return 0*x*t;
}
double u_0(double x) {
    return std::exp(-x);
}
double mu_0(double t) {
    return std::exp(t);
}
double mu_1(double t) {
    return -std::exp(t-1);
}
}
#endif // FUNCTIONS_H
