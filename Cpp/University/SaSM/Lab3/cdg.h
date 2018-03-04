#include "../Lab1/brvg.h"
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>


#ifndef LAB3_CDG_H
#define LAB3_CDG_H

//ccdf - continuous cumulative distribution function
namespace ccdf {

    double uniform(double x, double a = 0, double b = 1) {
        if (x < a) {
            return 0.;
        } else if (x > b) {
            return 1.;
        } else {
            return (x - a) / (b - a);
        }
    }

    double normal(double x, double a = 0, double sigma_sqr = 1) {
        return 1. / 2 * (1 + std::erf((x - a) / std::sqrt(2 * sigma_sqr)));
    }

    double cauchy(double x, double c, double m) {
        return 1. / 2 + 1. / M_PI * std::atan((x - m) / c);
    }

    double chi_squared(double x, size_t k = 1) {
        long double incomplete_gamma = 0;
        long double h = 1e-3;
        for (long double y = 0; y < x / 2 + 1e-4 - h; y += h) {
            long double y_half = y + h / 2;
            long double y_next = y + h;
            incomplete_gamma += std::exp(-y) * std::pow(y, k / 2 - 1);
            incomplete_gamma += 4 * std::exp(-y_half) *
                                std::pow(y_half, k / 2 - 1);
            incomplete_gamma += std::exp(-y_next) * std::pow(y_next, k / 2 - 1);
        }
        incomplete_gamma *= h / 6;
        return static_cast<double>(incomplete_gamma / std::tgamma(k / 2));
    }

    double logistic(double x, double mu, double k) {
        return 1. / (1 + std::exp(-(x - mu) / k));
    }

}
//cdg - continuous distribution generator
namespace cdg {

    std::vector<double> uniform(size_t n_sample = 1,
                                double a = 0, double b = 1) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double etha = brvg::single();
            sample[i] = (b - a) * etha + a;
        }
        return sample;
    }

    std::vector<double> exponential(size_t n_sample = 1, double lambda = 1.) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double etha = brvg::single();
            sample[i] = -1. * log(etha) / lambda;
        }
        return sample;
    }

    std::vector<double> gamma(size_t n_sample = 1, double lambda = 1., size_t k = 1) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            std::vector<double> exp_sample = cdg::exponential(k, 1. / lambda);
            for (int j= 0; j < k; j++) {
                sample[i] += exp_sample[j];
            }
        }
        return sample;
    }

    std::vector<double> normal(size_t n_sample = 1,
                               double a = 0, double sigma_sqr = 1) {
        std::vector<double> sample(n_sample);
        double sigma = std::sqrt(sigma_sqr);
        for (int i = 0; i < n_sample; i++) {
            double etha = 0;
            const int N = 1000;
            for (int j = 0; j < N; j++) {
                etha += brvg::single();
            }
            etha = std::sqrt(12. / N) * (etha - N / 2);
            sample[i] = etha * sigma + a;
        }
        return sample;
    }

    //bm - Box-Muller
    std::vector<double> normal_bm(size_t n_sample = 1,
                                  double a = 0, double sigma_sqr = 1) {
        std::vector<double> sample(n_sample);
        double sigma = std::sqrt(sigma_sqr);
        for (int i = 0; i < n_sample; i++) {
            double etha = brvg::single();
            double psi = brvg::single();
            sample[i] = sigma * std::sin(2. * M_PI * psi) *
                        std::sqrt(-2. * std::log(etha)) + a;
        }
        return sample;
    }

    std::vector<double> cauchy(size_t n_sample,
                               double c, double m) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double etha = brvg::single();
            sample[i] = m + c * std::tan(M_PI * (etha - 0.5));
        }
        return sample;
    }

    std::vector<double> chi_squared(size_t n_sample = 1, size_t k = 1) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double etha = 0;
            for (int j = 0; j < k; j++) {

                etha += std::pow(normal_bm()[0], 2);
            }
            sample[i] = etha;
        }
        return sample;
    }

    std::vector<double> student(size_t n_sample = 1, size_t m = 1) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            sample[i] = std::pow(normal_bm()[0], 2) / (chi_squared(m)[0] / m);
        }
        return sample;
    }

    std::vector<double> logistic(size_t n_sample, double mu, double k) {
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double etha = brvg::single();
            sample[i] = mu + k * std::log(etha / (1. - etha));
        }
        return sample;
    }

    //kt - Kolmogorov's test
    namespace kt {

        double uniform(const std::vector<double> &sample,
                       double a, double b) {
            size_t n = sample.size();
            std::vector<double> sorted_sample(n);
            std::copy(sample.begin(), sample.end(), sorted_sample.begin());
            std::sort(sorted_sample.begin(), sorted_sample.end());
            double statistic = -1 * std::numeric_limits<double>::max();
            for (int i = 0; i < n; i++) {
                statistic = std::max(statistic,
                                     ccdf::uniform(sorted_sample[i], a, b) -
                                     (2. * i + 1.) / (2 * n));
            }
            return statistic * std::sqrt(n);
        }

        double normal(const std::vector<double> &sample,
                      double a, double sigma_sqr) {
            size_t n = sample.size();
            std::vector<double> sorted_sample(n);
            std::copy(sample.begin(), sample.end(), sorted_sample.begin());
            std::sort(sorted_sample.begin(), sorted_sample.end());
            double statistic = -1 * std::numeric_limits<double>::max();
            for (int i = 0; i < n; i++) {
                statistic = std::max(statistic,
                                     ccdf::normal(sorted_sample[i],
                                                  a, sigma_sqr) -
                                     (2. * i + 1.) / (2 * n));
            }
            return statistic * std::sqrt(n);
        }

        double cauchy(const std::vector<double> &sample,
                      double c, double m) {
            size_t n = sample.size();
            std::vector<double> sorted_sample(n);
            std::copy(sample.begin(), sample.end(), sorted_sample.begin());
            std::sort(sorted_sample.begin(), sorted_sample.end());
            double statistic = -1 * std::numeric_limits<double>::max();
            for (int i = 0; i < n; i++) {
                statistic = std::max(statistic,
                                     ccdf::cauchy(sorted_sample[i], c, m) -
                                     (2. * i + 1.) / (2 * n));
            }
            return statistic * std::sqrt(n);
        }

        double chi_squared(const std::vector<double> &sample, size_t k = 1) {
            size_t n = sample.size();
            std::vector<double> sorted_sample(n);
            std::copy(sample.begin(), sample.end(), sorted_sample.begin());
            std::sort(sorted_sample.begin(), sorted_sample.end());
            double statistic = -1 * std::numeric_limits<double>::max();
            for (int i = 0; i < n; i++) {
                statistic = std::max(statistic,
                                     ccdf::chi_squared(sorted_sample[i], k) -
                                     (2. * i + 1.) / (2 * n));
            }
            return statistic * std::sqrt(n);
        }

        double logistic(const std::vector<double> &sample,
                        double mu, double k) {
            size_t n = sample.size();
            std::vector<double> sorted_sample(n);
            std::copy(sample.begin(), sample.end(), sorted_sample.begin());
            std::sort(sorted_sample.begin(), sorted_sample.end());
            double statistic = -1 * std::numeric_limits<double>::max();
            for (int i = 0; i < n; i++) {
                statistic = std::max(statistic,
                                     ccdf::logistic(sorted_sample[i], mu, k) -
                                     (2. * i + 1.) / (2 * n));
            }
            return statistic * std::sqrt(n);
        }
    }
}
#endif //LAB3_CDG_H
