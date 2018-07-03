#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include "../Lab1/brvg.h"

#ifndef LAB2_DDG_H
#define LAB2_DDG_H

const int MAX_VALUE = 4000000;

//ddg - discrete distribution generator
namespace ddg {
    std::vector<int> bernoulli(size_t n_sample, double p) {
        std::vector<int> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double a = brvg::single();
            if (a <= p) {
                sample[i] = 1;
            } else {
                sample[i] = 0;
            }
        }
        return sample;
    }

    std::vector<int> geometric(size_t n_sample, double p) {
        std::vector<int> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double a = brvg::single();
            sample[i] = static_cast<int>(std::log(a) / std::log(1 - p)) + 1;
        }
        return sample;
    }

    std::vector<int> negative_binomial(size_t n_sample, size_t m, double p) {
        std::vector<double> q(MAX_VALUE);
        double cur_probability = std::pow(p, m);
        q[0] = cur_probability;
        for (int i = 0; i < MAX_VALUE - 1; i++) {
            cur_probability *= (1 - p) * (i + m) / (i + 1);
            q[i + 1] = std::min(q[i] + cur_probability, 1.);
        }
        q[MAX_VALUE - 1] = 1.;
        std::vector<int> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double a = brvg::single();
            sample[i] = static_cast<int>(std::upper_bound(q.begin(),
                                                          q.end(), a) - q.begin());
        }
        return sample;
    }

    std::vector<int> hyperheometric(size_t n_sample, size_t n, size_t D, size_t N) {
        std::vector<double> q(MAX_VALUE);
        double cur_proba = 1;
        for (int i = 0; i < n; i++) {
            cur_proba *= 1. * (N - D - i) / (1. * (N - i));
        }
        q[0] = cur_proba;
        for (int i = 0; i < MAX_VALUE - 1; i++) {
            cur_proba *= 1. * (D - i) * (n - i) /
                         (1. * (i + 1) * (N - D - n + i + 1));
            q[i + 1] = std::min(q[i] + cur_proba, 1.);
        }
        q[MAX_VALUE - 1] = 1;
        std::vector<int> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double a = brvg::single();
            sample[i] = static_cast<int>(std::upper_bound(q.begin(),
                                                          q.end(), a) - q.begin());
        }
        return sample;
    }

    std::vector<int> uniform(size_t n_sample, const std::vector<int>& values) {
        std::vector<double> q(values.size());
        for (int i = 0; i < q.size(); i++) {
            q[i] = 1. * (i + 1) / values.size();
        }
        std::vector<int> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            double a = brvg::single();
            sample[i] = values[std::upper_bound(q.begin(),
                                                q.end(),
                                                a) - q.begin()];
        }
        return sample;
    }

    //pt - Pearson's test
    namespace pt {

        double bernoulli(const std::vector<int> &sample, double p) {
            size_t n = sample.size();
            std::vector<int> counts(2);
            for (int s : sample) {
                counts[s]++;
            }
            double statistic = std::pow(1. * counts[0] / n - (1 - p), 2) / (1 - p) +
                               std::pow(1. * counts[1] / n - p, 2) / p;
            return statistic * n;
        }

        double geometric(const std::vector<int> &sample, double p) {
            size_t n = sample.size();
            std::vector<double> proba(MAX_VALUE);
            proba[0] = p;
            for (int i = 1; i < proba.size(); i++) {
                proba[i] = proba[i - 1] * (1 - p);
            }
            std::vector<int> counts(MAX_VALUE);
            for (int i = 0; i < sample.size(); i++) {
                counts[std::min(sample[i], MAX_VALUE - 1)]++;
            }
            double statistic = 0;
            for (int i = 0; i < MAX_VALUE; i++) {
                if (proba[i] > 1e-6) {
                    statistic += std::pow(1. * counts[i] / n - proba[i], 2) / proba[i];
                }
            }
            return statistic * n;
        }

        double negative_binomial(const std::vector<int> &sample, double p, size_t m) {
            size_t n = sample.size();
            std::vector<double> proba(MAX_VALUE);
            proba[0] = std::pow(p, m);
            for (int i = 1; i < proba.size(); i++) {
                proba[i] = proba[i - 1] * (1 - p) * (i + m) / (i + 1);
            }
            std::vector<int> counts(MAX_VALUE);
            for (int i = 0; i < sample.size(); i++) {
                counts[std::min(sample[i], MAX_VALUE - 1)]++;
            }
            double statistic = 0;
            for (int i = 0; i < MAX_VALUE; i++) {
                if (proba[i] > 1e-6) {
                    statistic += std::pow(1. * counts[i] / n - proba[i], 2) / proba[i];
                }
            }
            return statistic * n;
        }

        double hyperheometric(const std::vector<int> &sample, size_t n, size_t D, size_t N) {
            std::vector<double> p(MAX_VALUE);
            p[0] = 1;
            for (int i = 0; i < n; i++) {
                p[0] *= 1. * (N - D - i) / (1. * (N - i));
            }
            for (int i = 1; i < p.size(); i++) {
                p[i] = p[i - 1] * (D - i) * (n - i) /
                       (1. * (i + 1) * (N - D - n + i + 1));
            }
            std::vector<int> counts(MAX_VALUE);
            for (int i = 0; i < sample.size(); i++) {
                counts[std::min(sample[i], MAX_VALUE - 1)]++;
            }
            double statistic = 0;
            for (int i = 0; i < MAX_VALUE; i++) {
                if (p[i] > 1e-6) {
                    statistic += std::pow(1. * counts[i] / sample.size() - p[i], 2) / p[i];
                }
            }
            return statistic * sample.size();
        }

        double uniform(const std::vector<int> &sample, const std::vector<int> &values) {
            size_t n = sample.size();
            std::vector<double> p(values.size(), 1. / values.size());
            std::unordered_map<int, int> indices;
            for (int i = 0; i < values.size(); i++) {
                indices[values[i]] = i;
            }
            std::vector<int> counts(values.size());
            for (int i : sample) {
                counts[indices[i]]++;
            }
            double statistic = 0;
            for (int i = 0; i < counts.size(); i++) {
                statistic += std::pow(1. * counts[i] / n - p[i], 2) / p[i];
            }
            return statistic * n;
        }

    }
}

#endif //LAB2_DDG_H
