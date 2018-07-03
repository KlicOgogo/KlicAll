#include <iostream>
#include "derivatives.h"
#include "methods.h"
#include "series.h"
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>

typedef long double ld;

int main() {
    std::ofstream of("out.txt");
    ld x = 1, xl = 1.5,  y = -2, step = 1./20., z;
    std::vector<ld> exact(10);
    exact = methods::exactSolution(x, xl, step);
    std::vector<ld> points(10);
    points = methods::series(x, xl, y, step);
    for (int i = 0; i < 10; i++) {
       std::cout << std::setprecision(10) << std::abs(points[i] - exact[i]) << ";   ";
       if (i % 2 != 0) {
           std::cout << '\n';
       }
    }
    points = methods::EulerExp(x, xl, y, step);
    for (int i = 0; i < 10; i++) {
       std::cout << std::setprecision(10) << std::abs(points[i] - exact[i]) << ";   ";
       if (i % 2 != 0) {
           std::cout << '\n';
       }
    }
    points = methods::EulerImp(x, xl, y, step);
    for (int i = 0; i < 10; i++) {
       std::cout << std::setprecision(10) << std::abs(points[i] - exact[i]) << ";   ";
       if (i % 2 != 0) {
           std::cout << '\n';
       }
    }
    points = methods::PredictorCorrector(x, xl, y, step);
    for (int i = 0; i < 10; i++) {
       std::cout << std::setprecision(10) << std::abs(points[i] - exact[i]) << ";   ";
       if (i % 2 != 0) {
           std::cout << '\n';
       }
    }
    points = methods::RungeKutta(x, xl, y, step);
    for (int i = 0; i < 10; i++) {
       std::cout << std::setprecision(10) << std::abs(points[i] - exact[i]) << ";   ";
       if (i % 2 != 0) {
           std::cout << '\n';
       }
    }
    points = methods::ExtAdams(x, xl, y, step);
    for (int i = 0; i < 10; i++) {
       std::cout << std::setprecision(10) << std::abs(points[i] - exact[i]) << ";   ";
       if (i % 2 != 0) {
           std::cout << '\n';
       }
    }
    x = 0;
    xl = 0.3;
    step = 0.03;
    y = 0.5;
    z = 1;
    methods::EulerExp(x, xl, y, z, step);
    methods::EulerImp(x, xl, y, z, step);
    methods::PredictorCorrector(x, xl, y, z, step);
    methods::RungeKutta(x, xl, y, z, step);
    methods::IntAdams(x, xl, y, z, step);
	
    return 0;
}
