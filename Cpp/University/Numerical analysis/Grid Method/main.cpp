#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "../RitzMethod/functions.h"

int main() {
    const int N = 10;
    std::vector<double> a(N+1), b(N+1), c(N+1), f(N+1);
    std::vector<double> gamma = {1, 3*std::tan(1)}, mu = {1, 0};
    const double step = 1./N;
    double x = 0.;
    b[0] = (func::k(x)+func::k(x+step))/(2*step);
    c[0] = step*func::q(x)/2 + b[0] + gamma[0];
    f[0] = step*func::f(x)/2 + mu[0];
    for (int i = 1; i < N; i++) {
        x += step;
        f[i] = func::f(x);
        a[i] = (func::k(x-step)+4*func::k(x)-func::k(x+step))/(4*step*step);
        b[i] = -a[i] + 8*func::k(x)/(4*step*step);
        c[i] = 8*func::k(x)/(4*step*step) + func::q(x);
    }
    a[N] = (func::k(x)+func::k(x+step))/(2*step);
    f[N] = step*func::f(x+step)/2 + mu[1];
    c[N] = step*func::q(x+step)/2 + a[N] + gamma[1];
    std::vector<double> alpha(N+2), beta(N+2);
    for (int i = 0; i <= N; i++) {
        alpha[i+1] = b[i]/(c[i]-alpha[i]*a[i]);
        beta[i+1] = (f[i]+beta[i]*a[i])/(c[i]-alpha[i]*a[i]);
    }
    std::vector<double> y(N+1);
    y[N] = beta[N+1];
    for (int i = N; i > 0; i--) {
        y[i-1] = alpha[i]*y[i]+beta[i];
    }
    for (int i = 0; i < N+1; i++) {
        std::cout << std::setprecision(6) << std::fixed << y[i] << '\n';
    }
    return 0;
}
