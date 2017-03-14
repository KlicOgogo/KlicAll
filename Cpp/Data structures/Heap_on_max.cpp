#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>

template<typename T>
class heapOnMax {
public:
    heapOnMax(std::vector<T> array) {
        array_ = array;
        heapSize_ = array.size();
        for (size_t i = array.size()-1; i > -1; i--) {
            sift_down(i);
        }
    }
    void insert(T value) {
        heapSize_++;
        array_.resize(heapSize_);
        array_[heapSize_-1] = value;
        sift_up(heapSize_-1);
    }
    void removeRoot() {
        std::swap(array_[0], array_[heapSize_-1]);
        array_.pop_back();
        heapSize_--;
        sift_down(0);
    }
    T getRootValue() {
        return array_[0];
    }

private:
    std::vector<T> array_;
    size_t heapSize_;
    void sift_down(size_t verticeIndex) {
        while (2*verticeIndex+1 < heapSize_) {
            size_t leftSonIndex = verticeIndex*2 + 1;
            size_t rightSonIndex = verticeIndex*2 + 2;
            if (rightSonIndex < heapSize_) {
                if (array_[rightSonIndex] > array_[leftSonIndex] && array_[rightSonIndex] > array_[verticeIndex]) {
                    std::swap(array_[verticeIndex], array_[rightSonIndex]);

                    verticeIndex = rightSonIndex;
                } else if (array_[rightSonIndex] < array_[leftSonIndex] && array_[leftSonIndex] > array_[verticeIndex]) {
                    std::swap(array_[verticeIndex], array_[leftSonIndex]);
                    verticeIndex = leftSonIndex;
                } else {
                    return;
                }
            } else {
                if (array_[leftSonIndex] > array_[verticeIndex]) {
                    std::swap(array_[verticeIndex], array_[leftSonIndex]);
                }
                return;
            }
        }
    }
    void sift_up(size_t verticeIndex) {
        while ((verticeIndex-1)/2 > 0) {
            size_t fatherIndex = (verticeIndex-1)/2;
            if (array_[fatherIndex] < array_[verticeIndex]) {
                std::swap(array_[verticeIndex], array_[fatherIndex]);
                verticeIndex = fatherIndex;
            } else {
                return;
            }
        }
    }
};

int main() {
    return 0;
}
