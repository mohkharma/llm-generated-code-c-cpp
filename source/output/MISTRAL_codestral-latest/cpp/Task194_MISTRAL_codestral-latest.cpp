#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class Master {
public:
    int guess(const std::string& word) {
        // Implementation of Master.guess is not provided
    }
};

class Solution {
public:
    void findSecretWord(std::vector<std::string>& words, Master& master) {
        std::unordered_map<std::string, int> matches;
        for (const auto& word : words) {
            for (const auto& other : words) {
                matches[word] += countMatches(word, other);
            }
        }

        std::vector<std::string> candidates = words;
        while (!candidates.empty()) {
            std::string guess = candidates.back();
            int numMatches = master.guess(guess);
            if (numMatches == 6) {
                return;
            }

            std::vector<std::string> newCandidates;
            for (const auto& candidate : candidates) {
                if (countMatches(guess, candidate) == numMatches) {
                    newCandidates.push_back(candidate);
                }
            }

            candidates = newCandidates;
        }
    }

private:
    int countMatches(const std::string& a, const std::string& b) {
        int count = 0;
        for (int i = 0; i < 6; i++) {
            if (a[i] == b[i]) {
                count++;
            }
        }
        return count;
    }
};
