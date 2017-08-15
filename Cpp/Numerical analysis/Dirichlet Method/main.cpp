#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "functions.h"

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
void print(std::vector<std::vector<double>> A_) {
    for (size_t i = 0; i < A_.size(); i++) {
        for (size_t j = 0; j < A_[0].size(); j++) {
            std::cout << std::setprecision(4) << std::fixed << A_[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    const int N = 20;
    std::vector< std::vector<double> > y(N+1);
    const double a = 0, c = 0;
    const double step = 1./N;
    double y_ = c;
    for (int j = 0; j < N+1; j++) {
        double x = a;
        y[j].resize(2*N+1);
        for (int i = 0; i < 2*N+1; i++) {
            if (j == 0) {
                y[j][i] = func::psi_3(x);
            } else if (j == N) {
                y[j][i] = func::psi_4(x);
            } else if (i == 0) {
                y[j][i] = func::psi_1(y_);
            } else if (i == 2*N) {
                y[j][i] = func::psi_2(y_);
            } else {
                y[j][i] = func::f(x, y_);
            }
            x += step;
        }
        y_ += step;
    }
    print(y);
    double maxResidual = 1;
    while (maxResidual > 1e-4) {
        maxResidual = 0;
        y_ = c+step;
        for (int j = 1; j < N; j++) {
            double x = a+step;
            for (int i = 1; i < 2*N; i++) {
                double temp = (y[j][i+1]+y[j][i-1]+y[j-1][i]+y[j+1][i]+
                        step*step*func::f(x, y_))/4;
                maxResidual = std::max(maxResidual, std::abs(y[j][i]-temp));
                y[j][i] = temp;
                x += step;
            }
            y_ += step;
        }
    }
    toFile(y, "output.txt");
    return 0;
}
