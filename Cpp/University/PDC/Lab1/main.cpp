#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>
#include <chrono>
#include <fstream>
#include <sstream>

const int N_TIMES = 2;

typedef std::vector<std::vector<int> > Matrix;
typedef std::vector<int> Vector;

Matrix random_matrix(size_t n_lines, size_t n_columns) {
    std::random_device device;
    std::default_random_engine generator(device());
    std::uniform_real_distribution<double> distribution(-101, 101);
    Matrix matrix(n_lines, Vector(n_columns));
    for (int i = 0; i < n_lines; i++) {
        for (int j = 0; j < n_columns; j++) {
            matrix[i][j] = static_cast<int>(distribution(generator));
        }
    }
    return matrix;
}

void print(const Matrix &A) {
    for (const auto &i : A) {
        for (int j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

Matrix product(const Matrix &A, const Matrix &B) {
    if (A[0].size() != B.size()) {
        throw std::runtime_error("Wrong sizes!");
    }
    Matrix C(A.size(), Vector(B[0].size()));
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < A[i].size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix product_omp(const Matrix &A, const Matrix &B, bool inner = false) {
    if (A[0].size() != B.size()) {
        throw std::runtime_error("Wrong sizes!");
    }
    Matrix C(A.size(), Vector(B[0].size()));
    #pragma omp parallel for if(!inner)
    for (int i = 0; i < A.size(); i++) {
        #pragma omp parallel for if(inner)
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < A[i].size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix product_block(const Matrix &A, const Matrix &B, size_t block_size = 1) {
    if (A[0].size() != B.size()) {
        throw std::runtime_error("Wrong sizes!");
    }
    Matrix C(A.size(), Vector(B[0].size()));
    for (int i = 0; i < A.size(); i += block_size) {
        for (int j = 0; j < B[0].size(); j += block_size) {
            for (int k = 0; k < A[0].size(); k += block_size) {
                size_t i_lim = std::min(i + block_size, A.size());
                size_t k_lim = std::min(k + block_size, A[0].size());
                size_t j_lim = std::min(j + block_size, B[0].size());
                for (int i_iter = i; i_iter < i_lim; i_iter++) {
                    for (int j_iter = j; j_iter < j_lim; j_iter++) {
                        for (int k_iter = k; k_iter < k_lim; k_iter++) {
                            C[i_iter][j_iter] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
    return C;
}

Matrix product_block_omp(const Matrix &A, const Matrix &B, size_t block_size = 1, bool inner = false) {
    if (A[0].size() != B.size()) {
        throw std::runtime_error("Wrong sizes!");
    }
    Matrix C(A.size(), Vector(B[0].size()));
    #pragma omp parallel for if(!inner)
    for (int i = 0; i < A.size(); i += block_size) {
        #pragma omp parallel for if(inner)
        for (int j = 0; j < B[0].size(); j += block_size) {
            for (int k = 0; k < A[0].size(); k += block_size) {
                size_t i_lim = std::min(i + block_size, A.size());
                size_t k_lim = std::min(k + block_size, A[0].size());
                size_t j_lim = std::min(j + block_size, B[0].size());
                for (int i_iter = i; i_iter < i_lim; i_iter++) {
                    for (int j_iter = j; j_iter < j_lim; j_iter++) {
                        for (int k_iter = k; k_iter < k_lim; k_iter++) {
                            C[i_iter][j_iter] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
    return C;
}

template <class T>
void SaveResultsBlock(T callable, const std::string &prefix, size_t matrix_size) {
    std::vector<size_t> block_sizes = {5, 10, 20, 25, 30, 40, 50, 60};
    std::stringstream ss;
    ss << prefix;
    ss << matrix_size;
    ss << ".txt";
    std::ofstream of(ss.str());
    for (auto block_size : block_sizes) {
        Matrix a = random_matrix(matrix_size, matrix_size), b = random_matrix(matrix_size, matrix_size);
        auto start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < N_TIMES; ++i) {
            callable(a, b, block_size);
        }
        auto end = std::chrono::steady_clock::now();
        auto average_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / N_TIMES;
        of << block_size << " " << average_time << std::endl;
        if (average_time > 100000) break;
    }
}

template <class T>
void SaveResults(T callable, const std::string &prefix, size_t block_size=0) {
    const static std::vector<size_t> range = {400, 800, 1000, 1500};
    std::stringstream ss;
    ss << prefix;
    ss << ".txt";
    std::ofstream of(ss.str());
    for (auto size : range) {
        Matrix a = random_matrix(size, size), b = random_matrix(size, size);
        auto start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < N_TIMES; ++i) {
            callable(a, b, block_size);
        }
        auto end = std::chrono::steady_clock::now();
        auto average_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / N_TIMES;
        of << size << " " << average_time << std::endl;
        if (average_time > 100000) break;
    }
}


int main() {
    const int MAX_THREADS_NUM = 4;
    for (int i = 1; i <= MAX_THREADS_NUM; ++i) {
        omp_set_num_threads(i);
        /*
        std::vector<size_t> matrix_sizes = {400, 1000, 1500};
        for (auto m_size : matrix_sizes) {
            SaveResultsBlock([](const Matrix& lhs, const Matrix& rhs, size_t matrix_size) {
                product_block(lhs, rhs, matrix_size);
            }, std::to_string(i) + "_seq_block_m_", m_size);
            SaveResultsBlock([](const Matrix& lhs, const Matrix& rhs, size_t block_size) {
                product_block_omp(lhs, rhs, block_size, true);
            }, std::to_string(i) + "_parallel_inner_block_m_", m_size);
            SaveResultsBlock([](const Matrix& lhs, const Matrix& rhs, size_t block_size) {
                product_block_omp(lhs, rhs, block_size);
            }, std::to_string(i) + "_parallel_outer_block_m_", m_size);
        }
        */
        SaveResults([](const Matrix& lhs, const Matrix& rhs, size_t matrix_size) {
            product_block(lhs, rhs, matrix_size);
        }, std::to_string(i) + "_seq_block", 25);
        SaveResults([](const Matrix& lhs, const Matrix& rhs, size_t block_size) {
            product_block_omp(lhs, rhs, block_size, true);
        }, std::to_string(i) + "_parallel_inner_block", 25);
        SaveResults([](const Matrix& lhs, const Matrix& rhs, size_t block_size) {
            product_block_omp(lhs, rhs, block_size);
        }, std::to_string(i) + "_parallel_outer_block", 25);

        SaveResults([](const Matrix& lhs, const Matrix& rhs, size_t block_size) {
            product(lhs, rhs);
        }, std::to_string(i) + "_pointwise_sequential");
        SaveResults([](const Matrix& lhs, const Matrix& rhs, size_t block_size) {
            product_omp(lhs, rhs);
        }, std::to_string(i) + "_pointwise_parallel");
    }
    return 0;
}
