#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct trie_node {
    trie_node *father;
    trie_node *suffix;
    std::unordered_map<std::string, trie_node*> children;
    std::vector<int> terminal;
    std::string last_line;

    trie_node() : father(nullptr), suffix(nullptr),
                  children(), last_line(), terminal() {}
};


trie_node *build_trie(const std::vector<std::vector<std::string>> &pattern) {
    trie_node *root = new trie_node();
    for (int i = 0; i < pattern.size(); i++) {
        trie_node *cur = root;
        for (int j = 0; j < pattern[i].size(); j++) {
            if (cur->children.find(pattern[i][j]) == cur->children.end()) {
                cur->children[pattern[i][j]] = new trie_node();
                cur->children[pattern[i][j]]->father = cur;
                cur->children[pattern[i][j]]->last_line = pattern[i][j];
            }
            cur = cur->children[pattern[i][j]];
        }
        cur->terminal.push_back(i);
    }
    return root;
}

void add_suffix_link(trie_node *node) {
    trie_node *cur = node->father;
    if (cur == nullptr) {
        node->suffix = node;
        return;
    }
    while (cur->father != nullptr) {
        cur = cur->suffix;
        if (cur->children.find(node->last_line) != cur->children.end()) {
            node->suffix = cur->children[node->last_line];
            return;
        }
    }
    node->suffix = cur;
}

void add_suffix_links(trie_node *root) {
    std::queue<trie_node *> trie_levels;
    trie_levels.push(root);
    while (!trie_levels.empty()) {
        trie_node *cur = trie_levels.front();
        add_suffix_link(cur);
        trie_levels.pop();
        for (auto it = cur->children.begin(); it != cur->children.end(); it++) {
                trie_levels.push(it->second);
        }
    }
}

trie_node *init_automation(const std::vector<std::vector<std::string> > &pattern) {
    trie_node *root = build_trie(pattern);
    add_suffix_links(root);
    return root;
}

trie_node *advance(trie_node *node, std::string line, std::vector<int> &terminal_index) {
    trie_node *cur = node;
    while (cur->father != nullptr) {
        if (cur->children.find(line) != cur->children.end()) {
            terminal_index = cur->children[line]->terminal;
            return cur->children[line];
        }
        cur = cur->suffix;
    }
    if (cur->children.find(line) != cur->children.end()) {
        terminal_index = cur->children[line]->terminal;
        return cur->children[line];
    } else {
        terminal_index = cur->terminal;
        return cur;
    }
}

std::vector<int> two_dim_matching(const std::vector<std::string> &text, const std::vector<std::vector<std::string> > &pattern) {
    trie_node *root = init_automation(pattern);
    std::vector<std::string> text_part(text.size());
    for (int i = 0; i < text.size(); i++) {
        std::string temp;
        for (int j = 0; j < pattern[0][0].size(); j++) {
            temp.push_back(text[i][j]);
        }
        text_part[i] = temp;
    }
    std::vector<int> matching_count(pattern.size());
    for (int j = 0; j < text[0].size() - pattern[0][0].size() + 1; j++) {
        trie_node* cur = root;
        for (int i = 0; i < text_part.size(); i++) {
            std::vector<int> indices;
            cur = advance(cur, text_part[i], indices);
            for (int& index: indices) {
                matching_count[index]++;
            }
        }
        if (j+pattern[0][0].size() < text[0].size()) {
            for (int i = 0; i < text_part.size(); i++) {
                text_part[i].erase(text_part[i].begin());
                text_part[i].push_back(text[i][j + pattern[0][0].size()]);
            }
        }
    }
    return matching_count;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    std::vector<std::string> text(n);
    for (int i = 0; i < n; i++) {
        std::cin >> text[i];
    }
    size_t t, k, l;
    std::cin >> t >> k >> l;
    std::vector<std::vector<std::string> > pattern(t, std::vector<std::string>(k));
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < k; j++) {
            std::cin >> pattern[i][j];
        }
    }
    std::vector<int> counts = two_dim_matching(text, pattern);
    for (int i = 0; i < counts.size(); i++) {
        std::cout << counts[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}