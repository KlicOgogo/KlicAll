#include <iostream>
#include <unordered_map>
#include <vector>



struct trie_node {
    trie_node *father;
    std::unordered_map<char, trie_node*> children;
    bool terminal;
    trie_node() : father(nullptr), children(), terminal() {}
};



trie_node* add_line(trie_node *root, const std::string &pattern, size_t &entered_count) {
    bool is_prefix = true;
    trie_node *cur = root;
    for (char i : pattern) {
        if (cur->children.find(i) == cur->children.end()) {
            is_prefix = false;
            cur->children[i] = new trie_node();
            cur->children[i]->father = cur;
        }
        cur = cur->children[i];
    }
    if (is_prefix) {
        if (!cur->terminal) {
            entered_count = pattern.size();
            cur->terminal = true;
        } else {
            if (cur->children.size() != 0) {
                entered_count = pattern.size();
            } else {
                cur = cur->father;
                int c = 0;
                while (cur->children.size() == 1 && cur != root && !cur->terminal) {
                    cur = cur->father;
                    ++c;
                }
                entered_count = pattern.size() - c;
            }
        }
    } else {
        entered_count = pattern.size();
        cur->terminal = true;
    }
    return root;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::string> words(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
    }
    trie_node *root = new trie_node();
    int sum = 0;
    size_t cur_entered;
    for (int i = 0; i < n; ++i) {
        root = add_line(root, words[i], cur_entered);
        sum += cur_entered;
    }
    std::cout << sum << '\n';
    return 0;
}