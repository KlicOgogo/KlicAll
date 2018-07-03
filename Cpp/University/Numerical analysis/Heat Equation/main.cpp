#include <iostream>
#include <vector>
#include <iomanip>
#include "functions.h"
#include <fstream>

void toFile (std::vector<std::vector<double>> A_, std::string fileName) {
    std::ofstream of(fileName);
    for (int i = A_.size()-1; i > -1; i--) {
        for (size_t j = 0; j < A_[0].size(); j++) {
            of << std::setprecision(4) << std::fixed << A_[i][j] << " ";
        }
        of << '\n';
    }
    of.close();
}

int main() {
    std::vector<double> alpha = {1, 0};
    std::vector<double> beta = {0, 1};
    const double sigma = 0.5, a = 0;
    const int N = 20;
    const double step = 1./N;
    double t = a;
    std::vector<std::vector<double>> y(N+1);
    for (int j = 0; j < N+1; j++) {
        double x = a;
        y[j].resize(N+1);
        if (j == 0) {
            for (int i = 0; i < N+1; i++) {
                y[j][i] = func::u_0(x);
                x += step;
            }
        }
        t += step;
    }
    t = a;
    for (int j = 0; j < N; j++) {
        double x = a;
        std::vector<double> a(N+1), b(N+1), c(N+1), f(N+1);
        a[0] = 0;
        b[0] = beta[0]/step;
        c[0] = b[0] - alpha[0] + beta[0]/2;
        f[0] = -func::mu_0(t+step) + (beta[0]*step/2)*(y[j][0]/step+func::f(x, t+step));
        x += step;
        for (int i = 1; i < N; i++) {
            a[i] = sigma/(step*step);
            b[i] = a[i];
            c[i] = (1./step) + 2*b[i];
            f[i] = y[j][i]/step + ((1-sigma)/(step*step))*(y[j][i+1]-2*y[j][i]+y[j][i-1]) +
                    func::f(x, t);
            x += step;
        }
        a[N] = beta[1]/step;
        b[N] = 0;
        c[N] = alpha[1] + a[N] + beta[1]/2;
        f[N] = func::mu_1(t+step) + (beta[1]*step/2)*(y[j][N]/step+func::f(x, t+step));
        std::vector<double> alpha_(N+2), beta_(N+2);
        for (int i = 0; i <= N; i++) {
            alpha_[i+1] = b[i]/(c[i]-alpha_[i]*a[i]);
            beta_[i+1] = (f[i]+beta_[i]*a[i])/(c[i]-alpha_[i]*a[i]);
        }
        y[j+1][N] = beta_[N+1];
        for (int i = N; i > 0; i--) {
            y[j+1][i-1] = alpha_[i]*y[j+1][i]+beta_[i];
        }
        t += step;
    }
    toFile(y, "output.txt");
    return 0;
}
