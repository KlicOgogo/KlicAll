#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct trie_node {
    trie_node* father;
    trie_node* suffix;
    std::vector<trie_node*> children;
    std::vector<int> terminal;
    int last_char;
    trie_node(): father(nullptr), suffix(nullptr),
                 children(std::vector<trie_node*>(26, nullptr)),
                 last_char(-1), terminal() {}
};

trie_node* build_trie(const std::vector<std::string>& pattern) {
    trie_node* root = new trie_node();
    for (int i = 0; i < pattern.size(); i++) {
        trie_node* cur = root;
        for (int j = 0; j < pattern[i].size(); j++) {
            if (cur->children[pattern[i][j] - 'a'] == nullptr) {
                cur->children[pattern[i][j] - 'a'] = new trie_node();
                cur->children[pattern[i][j] - 'a']->father = cur;
                cur->children[pattern[i][j] - 'a']->last_char = pattern[i][j] - 'a';
            }
            cur = cur->children[pattern[i][j] - 'a'];
        }
        cur->terminal.push_back(i);
    }
    return root;
}

void add_suffix_link(trie_node* node) {
    trie_node* cur = node->father;
    if (cur == nullptr) {
        node->suffix = node;
        return;
    }
    while (cur->father != nullptr) {
        cur = cur->suffix;
        if (cur->children[node->last_char] != nullptr) {
            node->suffix = cur->children[node->last_char];
            return;
        }
    }
    node->suffix = cur;
}

void add_suffix_links(trie_node* root) {
    std::queue<trie_node*> trie_levels;
    trie_levels.push(root);
    while (!trie_levels.empty()) {
        trie_node* cur = trie_levels.front();
        add_suffix_link(cur);
        trie_levels.pop();
        for (int i = 0; i < cur->children.size(); i++) {
            if (cur->children[i] != nullptr) {
                trie_levels.push(cur->children[i]);
            }
        }
    }
}

void count_terminal_indices(trie_node* root) {
    std::queue<trie_node*> trie_levels;
    trie_levels.push(root);
    while (!trie_levels.empty()) {
        trie_node* cur = trie_levels.front();
        if (cur->father != nullptr) {
            size_t old_size = cur->terminal.size();
            cur->terminal.resize(old_size + cur->suffix->terminal.size());
            std::copy(cur->suffix->terminal.begin(), cur->suffix->terminal.end(), cur->terminal.begin()+old_size);
        }
        trie_levels.pop();
        for (int i = 0; i < cur->children.size(); i++) {
            if (cur->children[i] != nullptr) {
                trie_levels.push(cur->children[i]);
            }
        }
    }
}

trie_node* init_automation(const std::vector<std::string>& pattern) {
    trie_node *root = build_trie(pattern);
    add_suffix_links(root);
    count_terminal_indices(root);
    return root;
}

trie_node* advance(trie_node* node, char ch, std::vector<int>& terminal_index) {
    trie_node* cur = node;
    while (cur->father != nullptr) {
        if (cur->children[ch-'a'] != nullptr) {
            terminal_index = cur->children[ch-'a']->terminal;
            return cur->children[ch-'a'];
        }
        cur = cur->suffix;
    }
    if (cur->children[ch-'a'] != nullptr) {
        terminal_index = cur->children[ch-'a']->terminal;
        return cur->children[ch-'a'];
    } else {
        terminal_index = cur->terminal;
        return cur;
    }
}

std::vector<int> aho_corasick(const std::vector<std::string>& pattern, const std::vector<std::string>& text) {
    trie_node* root = init_automation(pattern);
    std::vector<int> counts(pattern.size());
    for (int i = 0; i < text.size(); i++) {
        trie_node* cur = root;
        std::vector<bool> pattern_found(pattern.size());
        for (int j = 0; j < text[i].size(); j++) {
            std::vector<int> index;
            cur = advance(cur, text[i][j], index);
            for (int l = 0; l < index.size(); l++) {
                if (!pattern_found[index[l]]) {
                    counts[index[l]]++;
                    pattern_found[index[l]] = true;
                }
            }
        }
    }
    return counts;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::string> pattern(n);
    for (int i = 0; i < n; i++) {
        std::cin >> pattern[i];
    }
    size_t m;
    std::cin >> m;
    std::vector<std::string> text(m);
    for (int i = 0; i < m; i++) {
        std::cin >> text[i];
    }
    std::vector<int> counts = aho_corasick(pattern, text);
    for (int i = 0; i < counts.size(); i++) {
        std::cout << counts[i] << '\n';
    }
    return 0;
}
