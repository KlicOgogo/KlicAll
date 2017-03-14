#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

template <class RandomAccessIterator>
struct Bound {
    RandomAccessIterator lower_;
    RandomAccessIterator upper_;
    Bound(RandomAccessIterator lower, RandomAccessIterator upper):
        lower_(lower), upper_(upper) {}
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
    return Bound<RandomAccessIterator>(lowerBoundEqual+1, upperBoundGreater+1);
}

template <class RandomAccessIterator>
void QSort(RandomAccessIterator first, RandomAccessIterator last) {
    while (first < last-1) {
        typename std::iterator_traits<RandomAccessIterator>::value_type pivot = *(first+rand()%(last-first+1));
        Bound<RandomAccessIterator> index = Partition(first, last, pivot);
        if (index.lower_ - first < last-1 - index.upper_) {
            QSort(first, index.lower_);
            first = index.upper_;
        } else {
            QSort(index.upper_, last);
            last = index.lower_;
        }
    }
}

int main() {
    srand(time(nullptr));
    long long int n;
    std::cin >> n;
    std::vector<int> minutes(n);
    for (long long int i = 0; i < n; i++) {
        std::cin >> minutes[i];
    }
    long long int sum = 0;
    QSort(minutes.begin(), minutes.end());
    for (size_t i = 0; i < minutes.size(); i++) {
        sum += (n-i-1) * minutes[i];
    }
    std::cout << sum << std::endl;
    return 0;
}
