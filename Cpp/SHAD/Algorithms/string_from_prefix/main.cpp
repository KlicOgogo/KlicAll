#include <iostream>
#include <vector>

std::vector<int> string_from_correct_prefix(std::vector<int> prefix) {
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

std::vector<int> prefix_func(std::vector<int> string) {
    std::vector<int> prefix(string.size());
    for (int i = 1; i < string.size(); i++) {
        int border_length = prefix[i-1];
        while (string[border_length] != string[i] && border_length > 0) {
            border_length = prefix[border_length-1];
        }
        if (string[i] == string[border_length]) {
            prefix[i] = border_length + 1;
        }
    }
    return prefix;
}

bool is_correct_prefix(std::vector<int> prefix) {
    if (prefix[0] != 0) {
        return false;
    }
    for (int i = 1; i < prefix.size(); i++) {
        if (prefix[i] < 0 || prefix[i] > prefix[i-1]+1) {
            return false;
        }
    }
    std::vector<int> string = string_from_correct_prefix(prefix);
    std::vector<int> equal_prefix = prefix_func(string);
    for (int i = 0; i < prefix.size(); i++) {
        if (prefix[i] != equal_prefix[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> string_from_prefix(std::vector<int> prefix) {
    if (!is_correct_prefix(prefix)) {
        return std::vector<int>(1, -1);
    } else {
        return string_from_correct_prefix(prefix);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> prefix(n);
    for (int i = 0; i < n; i++) {
        std::cin >> prefix[i];
    }
    std::vector<int> string = string_from_prefix(prefix);
    for (int i = 0; i < string.size(); i++) {
        std::cout << string[i] << ' ';
    }
    return 0;
}