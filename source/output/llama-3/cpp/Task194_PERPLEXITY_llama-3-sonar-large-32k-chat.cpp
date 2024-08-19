#include <string>
#include <vector>
class Master {
public:
    int guess(const std::string& word) {
        // Implementation of Master.guess is not provided
    }
};
class Solution {
public:
    void findSecretWord(std::vector<std::string>& wordlist, Master* master) {
        for (int i = 0; i < 10; i++) {
            std::string guess = wordlist[rand() % wordlist.size()];
            int res = master->guess(guess);
            if (res == 6) return;
            std::vector<std::string> newList;
            for (std::string w : wordlist) {
                int match = 0;
                for (int j = 0; j < 6; j++) {
                    if (w[j] == guess[j]) match++;
                }
                if (match == res) newList.push_back(w);
            }
            wordlist = newList;
        }
    }
};
