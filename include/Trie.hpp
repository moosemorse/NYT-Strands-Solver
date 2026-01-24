#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <vector>

struct TrieNode {
    TrieNode* children[26] = {nullptr};
    bool isEndOfWord = false;

    ~TrieNode() {
        for (int i = 0; i < 26; ++i) {
            if (children[i]) delete children[i];
        }
    }

    void insert(const std::string& word) {
        TrieNode* curr = this;
        for (char c : word) {
            int idx = toupper(c) - 'A';
            if (idx < 0 || idx >= 26) continue;
            if (!curr->children[idx]) curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
        }
        curr->isEndOfWord = true;
    }
};

#endif