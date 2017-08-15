#include <iostream>
#include <vector>

typedef typename std::vector<int> Permutation;

Permutation radixSort(const std::vector< std::vector<int> >& elements, size_t c) {
    int length = elements[0].size();
    Permutation permutation(elements.size());
    for (size_t i = 1; i < elements.size(); i++) {
        permutation[i] = i;
    }
    for (int digit = length-1; digit >= 0; digit--) {
        std::vector<int> cases(c);
        for (size_t i = 0; i < permutation.size(); i++) {
            int digitValue = elements[permutation[i]][digit];
            cases[digitValue]++;
        }
        int count = 0;
        std::vector<int> howManyLess(c);
        for (size_t i = 0; i < cases.size(); i++) {
            howManyLess[i] = count;
            count += cases[i];
        }
        Permutation newPermutation(elements.size());
        for (size_t i = 0; i < permutation.size(); i++) {
            int digitValue = elements[permutation[i]][digit];
            newPermutation[howManyLess[digitValue]] = permutation[i];
            howManyLess[digitValue]++;
        }
        permutation = newPermutation;
    }
    return permutation;
}

int main() {
    size_t n, a, b, c;
    std::cin >> n >> a >> b >> c;
    std::vector< std::vector<int> > d(n);
    for (size_t i = 0; i < d.size(); i++) {
        d[i].resize(n);
    }
    int count;
    std::cin >> count;
    for (size_t i = 0; i < d.size(); i++) {
        for (size_t j = 0; j < d[i].size(); j++) {
            d[i][j] = count;
            count = (count*a + b) % c;
        }
    }
    Permutation permutation = radixSort(d, c);
    for (size_t i = 0; i < permutation.size(); i++) {
        std::cout << permutation[i] << " ";
    }
    return 0;
}
