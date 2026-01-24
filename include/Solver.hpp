#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Trie.hpp"
#include <vector>
#include <string>
#include <set>

class Solver {
public:
    Solver(const std::vector<std::vector<char>>& grid, TrieNode* root);
    std::vector<std::string> findWords(int r1, int r2, int c1, int c2);

private:
    void dfs(int r, int c, TrieNode* node, std::string current, 
             std::vector<std::vector<bool>>& visited, 
             int r1, int r2, int c1, int c2);
    
    const std::vector<std::vector<char>>& grid;
    TrieNode* root;
    std::set<std::string> found;
};

#endif