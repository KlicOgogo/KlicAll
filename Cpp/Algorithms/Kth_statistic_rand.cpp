#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <cassert>

template <class RandomAccessIterator>
struct Bound {
    RandomAccessIterator lower_;
    RandomAccessIterator upper_;
    Bound(RandomAccessIterator lower, RandomAccessIterator upper):
        lower_(lower), upper_(upper) {}
    Bound(): lower_(nullptr), upper_(nullptr) {}
};

template <class RandomAccessIterator>
Bound<RandomAccessIterator> Partition(RandomAccessIterator first, RandomAccessIterator last,
                                      typename std::iterator_traits<RandomAccessIterator>::value_type pivot) {
    RandomAccessIterator lowerBoundGreater = first;
    RandomAccessIterator upperBoundGreater = last-1;
    while (lowerBoundGreater < upperBoundGreater) {
        if (*lowerBoundGreater <= pivot) {
            lowerBoundGreater++;
        } else {
            std::swap(*lowerBoundGreater, *upperBoundGreater);
            upperBoundGreater--;
        }
    }
    while (*upperBoundGreater > pivot) {
        upperBoundGreater--;
    }
    RandomAccessIterator upperBoundEqual = upperBoundGreater;
    RandomAccessIterator lowerBoundEqual = first;
    while (lowerBoundEqual < upperBoundEqual) {
        if (*lowerBoundEqual < pivot) {
            lowerBoundEqual++;
        } else {
            std::swap(*lowerBoundEqual, *upperBoundEqual);
            upperBoundEqual--;
        }
    }
    while (*lowerBoundEqual < pivot) {
        lowerBoundEqual++;
    }
    return Bound<RandomAccessIterator>(lowerBoundEqual, upperBoundGreater);
}

template <class RandomAccessIterator>
typename std::iterator_traits<RandomAccessIterator>::value_type KthStatistic
    (RandomAccessIterator first, RandomAccessIterator last, size_t k) {
    RandomAccessIterator lowerBound = first;
    RandomAccessIterator upperBound = last;
    Bound<RandomAccessIterator> index(last, first);
    typename std::iterator_traits<RandomAccessIterator>::value_type pivot;
    while (first+k-1 < index.lower_ || first+k-1 > index.upper_) {
        pivot = *(lowerBound+rand() % (upperBound-lowerBound));
        index = Partition(lowerBound, upperBound, pivot);
        if (first+k-1 > index.upper_) {
            lowerBound = index.upper_+1;
        } else {
            upperBound = index.lower_;
        }
    }
    return *(first+k-1);
}

int main() {
    srand(time(nullptr));
    size_t T;
    std::cin >> T;
    std::vector<int> result(T);
    std::vector<int> result1(T);
    std::vector<int> test;
    size_t n, k;
    for (size_t i = 0; i < T; i++) {
        std::cin >> n >> k;
        assert(n >= k);
        test.resize(n);
        for (size_t j = 0; j < n; j++) {
            std::cin >> test[j];
        }
        result[i] = KthStatistic(test.begin(), test.end(), k);
        result1[i] = KthStatisti(test.begin(), test.end(), k);
        test.clear();
    }
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
        std::cout << result1[i] << std::endl;
    }
    return 0;
}
