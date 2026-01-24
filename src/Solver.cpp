#include "Solver.hpp"

Solver::Solver(const std::vector<std::vector<char>>& g, TrieNode* r) : grid(g), root(r) {}

void Solver::dfs(int r, int c, TrieNode* node, std::string current, 
                 std::vector<std::vector<bool>>& visited, 
                 int r1, int r2, int c1, int c2) {
    
    int idx = grid[r][c] - 'A';
    if (idx < 0 || idx >= 26 || !node->children[idx]) return;

    TrieNode* nextNode = node->children[idx];
    visited[r][c] = true;
    current += grid[r][c];

    if (nextNode->isEndOfWord && current.length() >= 4) {
        found.insert(current);
    }

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int nr = r + dr;
            int nc = c + dc;

            if (nr >= r1 && nr < r2 && nc >= c1 && nc < c2) {
                if (!visited[nr][nc]) {
                    dfs(nr, nc, nextNode, current, visited, r1, r2, c1, c2);
                }
            }
        }
    }

    visited[r][c] = false;
}

std::vector<std::string> Solver::findWords(int r1, int r2, int c1, int c2) {
    found.clear();
    
    int rows = grid.size();
    int cols = grid[0].size();

    for (int r = r1; r < r2; ++r) {
        for (int c = c1; c < c2; ++c) {
            std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
            dfs(r, c, root, "", visited, r1, r2, c1, c2);
        }
    }
    return {found.begin(), found.end()};
}