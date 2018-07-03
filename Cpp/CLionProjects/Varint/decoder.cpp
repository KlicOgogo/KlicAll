#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

void decode() {
    char k;
    std::vector<int> buf;
    while(fread(&k, 1, 1, stdin) == 1) {
        if (k < 0) {
            buf.emplace_back(k + 128);
        } else {
            buf.emplace_back(k);
            std::reverse(buf.begin(), buf.end());
            int num = 0;
            for (int i : buf) {
                num = num << 7;
                num += i;
            }
            std::cout << num << '\n';
            buf.clear();
        }
    }
}

int main() {
    decode();
    return 0;
}
