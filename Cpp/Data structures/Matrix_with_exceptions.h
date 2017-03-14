#include <vector>
#include <exception>

#ifndef MATRIX_H
#define MATRIX_H

#endif
#pragma once

class Matrix {
public:
    Matrix(std::vector< std::vector <int> > matrix) {
        for (int i = 0; i < matrix.size()-1; i++) {
            if (matrix[i].size() != matrix[i+1].size()) {
                throw std::length_error("constructor row length error");
            }
        }
        matrix_.resize(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            matrix_[i].resize(matrix[i].size());
            for (int j = 0; j < matrix[i].size(); j++) {
                matrix_[i][j] = matrix[i][j];
            }
        }
    }
    void print() const {
        for (int i = 0; i < matrix_.size(); i++) {
            for (int j = 0; j < matrix_[i].size(); j++) {
                std::cout << matrix_[i][j] << '\t';
            }
            std::cout << '\n';
        }
    }
    std::pair<size_t, size_t> size() const {
        return { matrix_.size(), matrix_[0].size() };
    }
    int get_elem(int row, int col) const {
        if (row < 0 || row >= matrix_.size()) {
            throw std::out_of_range("get_elem bad indexes");
        }
        if (col < 0 || col >= matrix_[row].size()) {
            throw std::out_of_range("get_elem bad indexes");
        }
        return matrix_[row][col];
    }
    Matrix operator+(const Matrix& other) {
        std::vector< std::vector<int> > matrix(matrix_.size());
        if (this->size().first != other.size().first || this->size().second != other.size().second) {
            throw std::length_error("operator+ size error");
        }
        for (int i = 0; i < matrix_.size(); i++) {
            matrix[i].resize(matrix_[i].size());
            for (int j = 0; j < matrix_[0].size(); j++) {
                matrix[i][j] = other.get_elem(i, j) + matrix_[i][j];
            }
        }
        return Matrix(matrix);
    }

private:
    std::vector < std::vector< int > > matrix_;
};
