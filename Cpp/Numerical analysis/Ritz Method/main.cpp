#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "functions.h"

void print(std::vector<std::vector<double>> A_) {
    for (size_t i = 0; i < A_.size(); i++) {
        for (size_t j = 0; j < A_[0].size(); j++) {
            std::cout << std::setprecision(7) << std::fixed << A_[i][j] << " ";
        }
        std::cout << '\n';
    }
}
void print(std::vector<double> b_) {
    for (size_t i = 0; i < b_.size(); i++) {
        std::cout << std::setprecision(7) << std::fixed << b_[i] << '\n';
    }
}

std::vector<double> solveGauss(const std::vector<std::vector<double> >& A, std::vector<double>& B_) {
    std::vector<std::vector<double>> A_(A.size());
    std::vector<double> B(B_.size());
    for (size_t i = 0; i < A.size(); i++) {
        A_[i].resize(A[i].size());
        B[i] = B_[i];
        for (size_t j = 0; j < A[i].size(); j++) {
            A_[i][j] = A[i][j];
        }
    }
    for (size_t i = 0; i < A_[0].size(); i++) {
        size_t top = i;
        double maxElem = A_[i][i];
        for (size_t j = i+1; j < A_.size(); j++) {
            if (std::abs(A_[j][i]) > std::abs(maxElem)) {
                top = j;
                maxElem = A_[j][i];
            }
        }
        if (top != i) {
            std::swap(A_[i], A_[top]);
            std::swap(B[i], B[top]);
        }
        for (size_t k = i+1; k < A_[i].size(); k++) {
            A_[i][k] /= A_[i][i];
        }
        B[i] /= A_[i][i];
        A_[i][i] = 1;
        for (size_t j = i+1; j < A_.size(); j++) {
            B[j] -= A_[j][i]*B[i];
            for (size_t k = i+1; k < A_[j].size(); k++) {
                A_[j][k] -= A_[i][k]*A_[j][i];
            }
            A_[j][i] = 0;
        }
    }
    for (int i = A_[0].size()-1; i > -1; i--) {
        for (int j = i-1; j > -1; j--) {
            B[j] -= B[i]*A_[j][i];
        }
    }
    return B;
}

int main() {
    const int n = 5;
    const int integralCount = 1000;
    std::vector< std::vector<double> > A(n);
    std::vector<double> b(n);
    for (int i = 0; i < n; i++) {
        A[i].resize(n);
    }
    double integralStep = 1./integralCount;
    for (size_t j = 0; j < b.size(); j++) {
        for (int i = 0; i < integralCount; i++) {
            double x = i*integralStep;
            func::phi phiPrev(x, 5);
            func::phi phiHalf(x + integralStep/2, 5);
            func::phi phiNext(x + integralStep, 5);
            b[j] += (integralStep/6)*(phiPrev.getF(j+1)*func::f(x) + 4*phiHalf.getF(j+1)*func::f(x + integralStep/2) +
                                      phiNext.getF(j+1)*func::f(x + integralStep));
            b[j] -= (integralStep/6)*(func::k(x)*phiPrev.getD(0)*phiPrev.getD(j+1) +
                                      func::q(x)*phiPrev.getF(0)*phiPrev.getF(j+1) +
                                    4*(func::k(x+integralStep/2)*phiHalf.getD(0)*phiHalf.getD(j+1) +
                                       func::q(x+integralStep/2)*phiHalf.getF(0)*phiHalf.getF(j+1)) +
                                      func::k(x+integralStep)*phiNext.getD(0)*phiNext.getD(j+1) +
                                      func::q(x+integralStep)*phiNext.getF(0)*phiNext.getF(j+1));
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < integralCount; k++) {
                double x = k*integralStep;
                func::phi phiPrev(x, 5);
                func::phi phiHalf(x + integralStep/2, 5);
                func::phi phiNext(x + integralStep, 5);
                A[j][i] += (integralStep/6)*(func::k(x)*phiPrev.getD(i+1)*phiPrev.getD(j+1) +
                                             func::q(x)*phiPrev.getF(i+1)*phiPrev.getF(j+1) +
                                           4*(func::k(x+integralStep/2)*phiHalf.getD(i+1)*phiHalf.getD(j+1) +
                                              func::q(x+integralStep/2)*phiHalf.getF(i+1)*phiHalf.getF(j+1)) +
                                             func::k(x+integralStep)*phiNext.getD(i+1)*phiNext.getD(j+1) +
                                             func::q(x+integralStep)*phiNext.getF(i+1)*phiNext.getF(j+1));
            }
        }
    }
    std::cout << "Matrix of system:\n";
    print(A);
    std::cout << "Vector of system:\n";
    print(b);
    std::vector<double> kek = solveGauss(A, b);
    const int N = 10;
    double step = 1./N;
    std::vector<double> result(N+1);
    for (int i = 0; i <= N; i++) {
        func::phi phi(i*step, 5);
        result[i] += phi.getF(0);
        for (size_t j = 1; j < n+1; j++) {
            result[i] += phi.getF(j)*kek[j-1];
        }
    }
    std::cout << "a_i:\n";
    print(kek);
    std::cout << "My Ritz method result:\n";
    print(result);
    return 0;
}
