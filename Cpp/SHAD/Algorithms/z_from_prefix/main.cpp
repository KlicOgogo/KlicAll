#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> string_from_correct_prefix(const std::vector<int>& prefix) {
    std::vector<int> string(prefix.size());
    int last_unique_character = 0;
    for (int i = 1; i < prefix.size(); i++) {
        if (prefix[i] == 0) {
            string[i] = ++last_unique_character;
        } else {
            string[i] = string[prefix[i]-1];
        }
    }
    return string;
}

std::vector<int> z_function(const std::vector<int>& string) {
    std::vector<int> z(string.size());
    int z_block_index = 0;
    for (int i = 1; i < string.size(); i++) {
        int lower_bound = std::min(z_block_index+z[z_block_index]-i, z[i-z_block_index]);
        z[i] = std::max(lower_bound, z[i]);
        while (string[z[i]] == string[i+z[i]] && i+z[i] < string.size()) {
            z[i]++;
        }
        if (i + z[i] >= z_block_index + z[z_block_index]) {
            z_block_index = i;
        }
    }
    return z;
}

std::vector<int> z_from_prefix(const std::vector<int>& prefix) {
    std::vector<int> string = string_from_correct_prefix(prefix);
    return z_function(string);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> prefix(n);
    for (int i = 0; i < n; i++) {
        std::cin >> prefix[i];
    }
    std::vector<int> z = z_from_prefix(prefix);
    for (int i = 0; i < z.size(); i++) {
        std::cout << z[i] << ' ';
    }
    return 0;
}