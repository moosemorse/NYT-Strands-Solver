#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include "Trie.hpp"
#include "Solver.hpp"

int main() {
    TrieNode* root = new TrieNode();
    std::ifstream dictFile("data/dictionary.txt");
    if (!dictFile) {
        std::cerr << "Error: Place dictionary.txt in the data/ folder.\n";
        return 1;
    }
    
    std::string word;
    while (dictFile >> word) {
        if (word.length() >= 4) root->insert(word);
    }

    
    std::ifstream gridFile("grid.txt");
    std::vector<std::vector<char>> gridChars(8, std::vector<char>(6));
    char ch;
    int count = 0;
    while (gridFile >> ch) {
        if (std::isalpha(ch)) {
            int r = count / 6;
            int c = count % 6;
            if (r < 8) gridChars[r][c] = std::toupper(ch);
            count++;
        }
    }

    Solver solver(gridChars, root);

    std::cout << "Enter r1 r2 c1 c2 [optional length]: ";
    std::string input;
    std::getline(std::cin >> std::ws, input);
    
    int r1 = 0, r2 = 8, c1 = 0, c2 = 6, targetLen = -1;
    std::stringstream ss(input);
    ss >> r1 >> r2 >> c1 >> c2 >> targetLen;

    // Debug: Print the loaded grid to console
    std::cout << "Loaded Grid (8x6):" << std::endl;
    for (int i {}; i < 8; ++i) {
        for (int j {}; j < 6; ++j) {
            std::cout << gridChars[i][j] << " ";
        }
        std::cout << std::endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto rawResults = solver.findWords(r1, r2, c1, c2);
    
    std::vector<std::string> finalResults;
    for (const auto& w : rawResults) {
        if (targetLen == -1 || (int)w.length() == targetLen) {
            finalResults.push_back(w);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::ofstream outFile("results.txt");
    outFile << "Search Time: " << elapsed.count() << " ms\n";
    outFile << "Words Found: " << finalResults.size() << "\n\n";
    for (const auto& w : finalResults) outFile << w << "\n";

    std::cout << "Done! Found " << finalResults.size() << " words in " << elapsed.count() << " ms.\n";
    
    delete root;
    return 0;
}