#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    int max_level = 0;
    std::vector<int> levels(n);
    std::stack<char> braces;
    std::stack<int> indices;
    for (int i = 0; i < n; i++) {
        if (s[i] == '[') {
            braces.push(s[i]);
            indices.push(i);
            max_level = std::max(max_level, (int) braces.size());
        } else if (s[i] == ']') {
            levels[i] = (int) braces.size();
            levels[indices.top()] = (int) braces.size();
            braces.pop();
            indices.pop();
        }
    }
    int num_of_strs = max_level * 2 + 1;
    std::vector<std::string> out(num_of_strs);
    for (auto i = 0; i < out.size(); i++) {
        out[i].resize(5*n);
        for (int j = 0; j < out[i].size()-1; j++) {
            out[i][j] = ' ';
        }
    }
    int print_index = 0;
    int last_index;
    for (int i = 0; i < n; i++, print_index++) {
        if (s[i] == '[') {
            out[levels[i]-1][print_index] = '+';
            out[out.size()-levels[i]][print_index] = '+';
            out[levels[i]-1][print_index+1] = '-';
            out[out.size()-levels[i]][print_index+1] = '-';
            for (int j = levels[i]; j < out.size()-levels[i]; j++) {
                out[j][print_index] = '|';
            }
            if (i+1 < n && s[i+1] == ']') {
                print_index += 2;
            }
        } else {
            out[levels[i] - 1][print_index] = '-';
            out[out.size() - levels[i]][print_index] = '-';
            out[levels[i] - 1][print_index + 1] = '+';
            out[out.size() - levels[i]][print_index + 1] = '+';
            for (int j = levels[i]; j < out.size() - levels[i]; j++) {
                out[j][print_index + 1] = '|';
            }
            if (i + 1 < n && s[i + 1] == '[') {
                print_index++;
            } else if (i + 1 == n) {
                for (int j = 0; j < out.size(); j++) {
                    out[j][print_index + 2] = 0;
                    last_index = print_index+2;
                }
            }
        }
    }
    for (int i = 0; i < out.size(); i++) {
        for (int j = 0; j < last_index; j++) {
            std::cout << out[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}