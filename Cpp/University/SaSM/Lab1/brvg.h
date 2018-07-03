#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

#ifndef LAB1_BRVG_H
#define LAB1_BRVG_H

// brvg - basic random value generator

namespace brvg {

    double single() {
        std::random_device device;
        std::default_random_engine generator(device());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

// lc - linear congruential
    std::vector<double> lc(int first_value, int beta, size_t n_sample) {
        const uint64_t M = 2147486648;
        std::vector<double> sample(n_sample);
        auto cur_value = static_cast<uint64_t>(first_value);
        for (int i = 0; i < n_sample; i++) {
            sample[i] = 1. * cur_value / M;
            cur_value = (cur_value * beta) % M;
        }
        return sample;
    }

// sr - standard random
    std::vector<double> sr(size_t n_sample) {
        std::random_device device;
        std::default_random_engine generator(device());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        std::vector<double> sample(n_sample);
        for (int i = 0; i < n_sample; i++) {
            sample[i] = distribution(generator);
        }
        return sample;
    }

// mm - MacLaren-Marsaglia
    std::vector<double> mm_sr_based(size_t K, size_t n_sample) {
        auto b = sr(n_sample);
        auto c = sr(n_sample);
        std::vector<double> sample(n_sample);
        std::vector<double> V(K);
        std::copy(b.begin(), b.begin() + K, V.begin());
        for (int i = 0; i < n_sample; i++) {
            sample[i] = V[K * c[i]];
            V[K * c[i]] = b[(i + K) % b.size()];
        }
        return sample;
    }

    // pc - precision criterion
    namespace pc {
        std::pair<double, double> moments(const std::vector<double> &sample) {
            size_t n = sample.size();
            const double E = 0.5;
            const double DISP = 1. / 12;
            double e_smpl = 0;
            for (int i = 0; i < n; i++) {
                e_smpl += sample[i];
            }
            e_smpl /= n;
            double disp_smpl = 0;
            for (int i = 0; i < n; i++) {
                disp_smpl += std::pow(sample[i] - e_smpl, 2);
            }
            disp_smpl /= n - 1;
            double e_eps = std::abs(E - e_smpl);
            double disp_eps = std::abs(DISP - disp_smpl);
            double c_e = std::sqrt(12. * n);
            double temp = 0.0056 * std::pow(1. * n, -1) +
                          0.0028 * std::pow(1. * n, -2) -
                          0.0083 * std::pow(1. * n, -3);
            double c_disp = 1. * (n - 1) * std::pow(temp, -0.5) / n;
            return std::make_pair(c_e * e_eps, c_disp * disp_eps);
        }

        double kolmogorov(const std::vector<double> &sample) {
            size_t n = sample.size();
            std::vector<double> sorted_sample(n + 2);
            std::copy(sample.begin(), sample.end(), sorted_sample.begin());
            sorted_sample[n + 1] = 1.;
            std::sort(sorted_sample.begin(), sorted_sample.end());
            double sup = 0;
            for (int i = 0; i < n; i++) {
                sup = std::max(sup, std::abs(sorted_sample[i] - 1. * i / n));
                sup = std::max(sup, std::abs(sorted_sample[i + 1] - 1. * i / n));
            }
            return sup;
        }

        double pearson(const std::vector<double> &sample, size_t n_intervals) {
            size_t n = sample.size();
            std::vector<int> sample_counts(n_intervals);
            for (int i = 0; i < n; i++) {
                sample_counts[n_intervals * sample[i]]++;
            }
            std::vector<double> thetas(n_intervals, 1. / n_intervals);
            double statistic = 0;
            for (int i = 0; i < n_intervals; i++) {
                statistic += std::pow(1. * sample_counts[i] / n - thetas[i], 2) /
                             thetas[i];
            }
            statistic *= n;
            return statistic;
        }
    }

}

#endif //LAB1_BRVG_H
