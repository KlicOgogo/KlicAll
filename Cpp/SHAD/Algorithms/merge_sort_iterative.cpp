#include <iostream>
#include <algorithm>
#include <vector>

template <class RandomAccessIterator>
    void Merge(RandomAccessIterator firstFirst, RandomAccessIterator firstLast,
    RandomAccessIterator secondFirst, RandomAccessIterator secondLast) {
        RandomAccessIterator tempFirst = firstFirst;
        RandomAccessIterator tempSecond = secondFirst;
        std::vector <typename std::iterator_traits<RandomAccessIterator>::value_type> temp;
        temp.reserve(firstLast-firstFirst+secondLast-secondFirst);
        while (firstFirst < firstLast && secondFirst < secondLast) {
            if (*firstFirst <= *secondFirst) {
                temp.push_back(*firstFirst);
                firstFirst++;
            } else {
                temp.push_back(*secondFirst);
                secondFirst++;
            }
        }
        temp.resize(firstLast-tempFirst+secondLast-tempSecond);
        std::copy(firstFirst, firstLast, temp.end()+(firstFirst-firstLast));
        std::copy(secondFirst, secondLast, temp.end()+(secondFirst-secondLast));
        std::copy(temp.begin(), temp.end(), tempFirst);
    }

template <class RandomAccessIterator>
    void MergeSort(RandomAccessIterator first, RandomAccessIterator last) {
        int SizeToMerge = 1;
        while (SizeToMerge < last-first) {
            int MergeStep = 0;
            int Step = 2*SizeToMerge;
            for (; first+Step+MergeStep < last; MergeStep += Step) {
                Merge(first+MergeStep, first+MergeStep+SizeToMerge,
                      first+MergeStep+SizeToMerge, first+Step+MergeStep);
            }
            if (first+SizeToMerge+MergeStep > last) {
                Merge(first+MergeStep, last,
                      last, last);
            } else {
                Merge(first+MergeStep, first+SizeToMerge+MergeStep,
                      first+SizeToMerge+MergeStep, last);
            }
            SizeToMerge *= 2;
        }
    }

int main() {
    long long int n;
    std::cin >> n;
    std::vector<int> minutes(n);
    for (int i = 0; i < n; i++) {
        std::cin >> minutes[i];
    }
    long long int sum = 0;
    MergeSort (minutes.begin(), minutes.end());
    for (size_t i = 0; i < minutes.size(); i++) {
        sum += (n-i-1) * minutes[i];
    }
    std::cout << sum << std::endl;
    return 0;
}
