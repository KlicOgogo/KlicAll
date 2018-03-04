#include "../Lab3/cdg.h"
#include "../Lab2/ddg.h"
#include <cmath>

typedef std::vector<double> Vector;
typedef std::vector<std::vector<double> > Matrix;

#ifndef LAB4_MCM_H
#define LAB4_MCM_H

namespace func {

    double sgn(double x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }
    }

    double f(double x) {
        return x * std::log(x) / (1 + x * x);
    }

    double rho(double x) {
        return std::exp(-x);
    }

    double f(double r, double phi) {
        return r * sgn(r * r * std::cos(2 * phi) + 2);
    }

    double rho(double r, double phi) {
        return 1. / (4 * M_PI) + r*0 + phi*0;
    }
}

//mcm - Monle-Carlo method
namespace mcm {

    // counts integral from 0 to \inf f(x) dx
    double count_1D_integral(size_t n_iters) {
        double integral = 0;
        for (int i = 0; i < n_iters; i++) {
            double x = -std::log(1 - cdg::uniform()[0]);
            integral += func::f(x) / func::rho(x);
        }
        return integral / n_iters;
    }

    // counts integral r from 0 to 2, phi from 0 to 2*PI f(r, phi) dr d(phi)
    double count_2D_integral(size_t n_iters) {
        double integral = 0;
        for (int i = 0; i < n_iters; i++) {
            double r = cdg::uniform(1, 0, 2)[0];
            double phi = cdg::uniform(1, 0, 2 * M_PI)[0];
            integral += func::f(r, phi) / func::rho(r, phi);
        }
        return integral / n_iters;
    }

    // solves system x = Ax + f
    Vector solve_linear_system(const Matrix &A, const Vector &f,
                               size_t chain_length,
                               size_t chain_number) {
        size_t n = f.size();
        Matrix P(n, Vector(n, 1. / n));
        Vector pi(n, 1. / n);
        Vector answer(n);
        for (int k = 0; k < n; k++) {
            Vector h(n);
            h[k] = 1;
            Vector g(n);
            for (int i = 0; i < n; i++) {
                g[i] = h[i] / pi[i];
            }
            Matrix G(n, Vector(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    G[i][j] = A[i][j] / P[i][j];
                }
            }
            for (int i = 0; i < chain_number; i++) {
                std::vector<int> chain(chain_length);
                Vector Q(chain_length);
                std::vector<int> values(n);
                for (int j = 1; j < n; j++) {
                    values[j] = j;
                }
                double psi = 0;
                //pi^{(t+1)} = ... = pi^{(0)}
                chain[0] = ddg::uniform(1, values)[0];
                Q[0] = g[chain[0]];
                psi += Q[0] * f[chain[0]];
                for (int j = 1; j < chain_length; j++) {
                    chain[j] = ddg::uniform(1, values)[0];
                    Q[j] = Q[j - 1] * G[chain[j - 1]][chain[j]];
                    psi += Q[j] * f[chain[j]];
                }
                answer[k] += psi;
            }
            answer[k] /= chain_number;
        }
        return answer;
    }

}
#endif //LAB4_MCM_H
