#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> count_rank_array(const std::vector<int>& suffix_array) {
    std::vector<int> rank_array(suffix_array.size());
    for (int i = 0; i < suffix_array.size(); i++) {
        rank_array[suffix_array[i]] = i;
    }
    return rank_array;
}

std::vector<int> count_lcp_array(const std::string& s, const std::vector<int>& suffix_array) {
    std::vector<int> lcp_array(suffix_array.size());
    std::vector<int> rank_array = count_rank_array(suffix_array);
    int lb = 0;
    for (int i = 0; i < suffix_array.size(); i++) {
        int cur = rank_array[i];
        if (rank_array[i] != suffix_array.size() - 1) {
            while (std::max(suffix_array[cur] + lb, suffix_array[cur + 1] + lb) <
                   suffix_array.size() && s[suffix_array[cur] + lb] == s[suffix_array[cur + 1] + lb]) {
                lb++;
            }
            lcp_array[cur] = lb;
            lb = std::max(--lb, 0);
        }
    }
    return lcp_array;
}

int count_max_lcp(const std::string& s, const std::vector<int>& suffix_array) {
    std::vector<int> lcp_array = count_lcp_array(s, suffix_array);
    return *(std::max_element(lcp_array.begin(), lcp_array.end()));
}

int count_unique_lcp_lengths(const std::string& s, const std::vector<int>& suffix_array) {
    std::vector<int> lcp_array = count_lcp_array(s, suffix_array);
    std::vector<bool> lcp_has_len(lcp_array.size());
    for (int i = 0; i < lcp_array.size(); i++) {
        lcp_has_len[lcp_array[i]] = true;
    }
    return (int) std::count(lcp_has_len.begin(), lcp_has_len.end(), true);
}

uint64_t count_unique_substrings(const std::string& s, const std::vector<int>& suffix_array) {
    std::vector<int> lcp_array = count_lcp_array(s, suffix_array);
    uint64_t count = 0;
    for (int i = 0; i < suffix_array.size(); i++) {
        count += suffix_array.size() - suffix_array[i] - lcp_array[i];
    }
    return ++count;
}

int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> suffix_array(s.size());
    for (int i = 0; i < s.size(); i++) {
        std::cin >> suffix_array[i];
    }
    uint64_t unique_substrings = count_unique_substrings(s, suffix_array);
    int unique_lengths = count_unique_lcp_lengths(s, suffix_array);
    int max_lcp = count_max_lcp(s, suffix_array);
    std::cout << unique_substrings << ' ' << max_lcp << ' ' << unique_lengths << '\n';
    return 0;
}
