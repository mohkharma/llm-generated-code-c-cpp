#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */

class Master {
private:
    std::string secret;
    int guesses;

public:
    Master(std::string s) : secret(s), guesses(0) {}

    int guess(std::string word) {
        guesses++;
        int matches = 0;
        for (int i = 0; i < 6; i++) {
            if (secret[i] == word[i]) {
                matches++;
            }
        }
        return matches;
    }

    int getGuesses() {
        return guesses;
    }
};
class Solution {
public:
    std::vector<std::vector<int>> H;
    
    void findSecretWord(std::vector<std::string>& words, Master& master) {
        int n = words.size();
        H.resize(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int matches = 0;
                for (int k = 0; k < 6; ++k) {
                    if (words[i][k] == words[j][k]) {
                        matches++;
                    }
                }
                H[i][j] = H[j][i] = matches;
            }
        }

        std::vector<int> possible(n);
        iota(possible.begin(), possible.end(), 0);
        
        int matches = 0;
        while (matches < 6) {
            int guess = findBestGuess(possible, words);
            matches = master.guess(words[guess]);
            if (matches == 6) {
                break;
            }
            std::vector<int> newPossible;
            for (int j : possible) {
                if (H[guess][j] == matches) {
                    newPossible.push_back(j);
                }
            }
            possible = newPossible;
        }
    }
    
private:
    int findBestGuess(const std::vector<int>& possible, const std::vector<std::string>& words) {
        int minMaxGroupSize = possible.size();
        int ans = -1;
        for (int i : possible) {
            std::vector<int> groups(7, 0);
            for (int j : possible) {
                if (i != j) {
                    groups[H[i][j]]++;
                }
            }
            int maxGroupSize = *max_element(groups.begin(), groups.end());
            if (maxGroupSize < minMaxGroupSize) {
                minMaxGroupSize = maxGroupSize;
                ans = i;
            }
        }
        return ans;
    }
};