#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <unordered_set>

const uint64_t POWW = 65536;

std::string binary(uint64_t a) {
    std::string result;
    int i = 0;
    while (a > 0 || i < 64) {
        if (a > 0) {
            result.push_back(std::to_string(a % 2)[0]);
            a = a >> 1;
        } else {
            result.push_back('0');
        }
        ++i;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int hamming_distance(const uint64_t &a, const uint64_t &b) {
    auto c = a ^ b;
    int dist = 0;
    while (c > 0) {
        if (c % 2 == 1) {
            ++dist;
        }
        c = c >> 1;
    }
    return dist;
}

std::vector<uint64_t> read_data(const std::string &filename) {
    FILE *file;
    file = fopen(filename.c_str(), "r");
    std::vector<uint64_t> numbers;
    unsigned long long int num;
    while (1 == fscanf(file, "%llu", &num)) {
        numbers.emplace_back(num);
    }
    return numbers;
}

std::vector<std::unordered_map<uint64_t,
        std::unordered_set<uint64_t>>> get_indices(const std::vector<uint64_t> &numbers) {
    std::vector<std::unordered_map<uint64_t, std::unordered_set<uint64_t>>> index(4);
    for (int i = 0; i < numbers.size(); ++i) {
        auto temp = numbers[i];
        for (int j = 0; j < index.size(); ++j) {
            uint64_t ind = temp % POWW;
            if (index[j].find(ind) == index[j].end()) {
                index[j][ind] = std::unordered_set<uint64_t>();
            }
            index[j][ind].insert(numbers[i]);
            temp = temp >> 16;
        }
    }
    return index;
};

int main() {
    auto numbers = read_data("simhash_sorted.txt");
    auto index = get_indices(numbers);
    std::unordered_map<uint64_t, int> numind;
    for (int i = 0; i < numbers.size(); ++i) {
        numind[numbers[i]] = i;
    }
    std::vector<bool> has_group(numbers.size());
    size_t min_without = 0;
    std::map<int, int> sizes_map;
    while (min_without < numbers.size()) {
        std::vector<uint64_t> group;
        auto group_head = numbers[min_without];
        group.emplace_back(group_head);
        has_group[min_without] = true;
        int group_size = 1;
        auto for_ind = numbers[min_without];
        for (int j = 0; j < index.size(); ++j) {
            for (auto it = index[j][for_ind % POWW].begin();
                 it != index[j][for_ind % POWW].end(); ++it) {
                if (hamming_distance(group_head, *it) < 4) {
                    if (!has_group[numind[*it]]) {
                        has_group[numind[*it]] = true;
                        group.emplace_back(*it);
                        ++group_size;
                    }
                }
            }
            for_ind = for_ind >> 16;
        }
        for (int i = 0; i < group.size(); ++i) {
            for (int j = 0; j < index.size(); ++j) {
                for (auto it = index[j].begin(); it != index[j].end(); ++it) {
                    if (it->second.find(group[i]) != it->second.end()) {
                        it->second.erase(group[i]);
                    }
                }
            }
        }
        if (sizes_map.find(group_size) == sizes_map.end()) {
            sizes_map[group_size] = 1;
        } else {
            ++sizes_map[group_size];
        }
        while (has_group[min_without]) {
            ++min_without;
        }
    }
    std::ofstream out("result.txt");
    int sum = 0;
    for (auto it = sizes_map.begin(); it != sizes_map.end(); ++it) {
        out << it->first << ' ' << it->second << '\n';
        sum += it->first * it->second;
    }
    out.close();
    std::cout << sum << '\n';
    return 0;
}