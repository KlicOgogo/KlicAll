#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    long long int x;
    std::cin >> x;
    if (x == 1000000000000000000) {
        std::cout << 999999999999999999 << '\n';
        return 0;
    }
    int digit_count = 0;
    long long int last_digit = -1;
    int sum_count = 0;
    long long int temp_x = x;
    while (temp_x != 0) {
        long long int digit = temp_x % 10;
        sum_count += digit;
        digit_count++;
        temp_x /= 10;
        if (temp_x == 0) {
            last_digit = digit;
        }
    }
    if (sum_count >= last_digit-1+(digit_count-1)*9) {
        std::cout << x << '\n';
    }
    else {
        long long int result = -1;
        std::vector<long long int> digits(digit_count);
        std::vector<long long int> digits2(digit_count);
        for (int i = 0; i < digit_count-1; i++) {
            digits[i] = 9;
            digits2[i] = 9;
        }
        digits2[0] = last_digit;
        digits[digits.size()-1] = last_digit-1;
        digits2[digits2.size()-1] = 8;
        for (int i = digit_count-1; i >= 0; i--) {
            long long int y = digits[0];
            long long int y2 = digits2[0];
            for (auto j = 1; j < digit_count; j++) {
                y2 *= 10;
                y *= 10;
                y2 += digits2[j];
                y += digits[j];

            }
            if (y >= x) {
                if (i > 0) {
                    std::swap(digits[i], digits[i - 1]);
                }
            }
            else {
                result = std::max(result, y);
            }
            if (y2 >= x) {
                if (i > 0) {
                    std::swap(digits2[i], digits2[i - 1]);
                }
            }
            else {
                result = std::max(result, y2);
            }
        }
        std::cout << result << '\n';
    }
    return 0;
}