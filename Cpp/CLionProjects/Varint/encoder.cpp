#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>

size_t encode() {
    int number;
    size_t sum = 0;
    while (std::cin >> number) {
        while (number > 127) {
            char block = number % 128 + 128;
            std::fwrite(&block, 1, 1, stdout);
            number = number >> 7;
            ++sum;
        }
        char block = number % 128;
        std::fwrite(&block, 1, 1, stdout);
        ++sum;
    }
    return sum;
}

int main() {
    auto sum = encode();
    std::ofstream out("log.txt", std::ios::out | std::ios::app);
    out << sum << '\n';
    out.close();
    return 0;
}
