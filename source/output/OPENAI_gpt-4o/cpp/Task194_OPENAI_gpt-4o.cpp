#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

//compilation error, error: 'words' was not declared in this scope; did you mean 'word'?


using namespace std;

class Master {
private:
    string secret;
    //add defintion of words here to fix error: 'words' was not declared in this scope; did you mean 'word'?
    vector<string> words;

public:
    int guess_count;

    Master(string sec, vector<string> word_list) : secret(sec), words(word_list), guess_count(0) {}

    int guess(string word) {
        guess_count++;
        if (find(words.begin(), words.end(), word) == words.end()) {
            return -1;
        }
        int matches = 0;
        for (int i = 0; i < secret.size(); i++) {
            if (secret[i] == word[i]) {
                matches++;
            }
        }
        return matches;
    }
};

int match_count(string w1, string w2) {
    int count = 0;
    for (int i = 0; i < w1.size(); i++) {
        if (w1[i] == w2[i]) {
            count++;
        }
    }
    return count;
}

void findSecretWord(vector<string>& words, Master& master, int allowedGuesses) {
    for (int i = 0; i < allowedGuesses; i++) {
        string guessWord = words[rand() % words.size()];
        int matches = master.guess(guessWord);

        if (matches == 6) {
            cout << "You guessed the secret word correctly." << endl;
            return;
        }

        vector<string> newWords;
        for (string word : words) {
            if (match_count(word, guessWord) == matches) {
                newWords.push_back(word);
            }
        }
        words = newWords;
    }
    cout << "Either you took too many guesses, or you did not find the secret word." << endl;
}

int main() {
    srand(time(0));  // Seed the random number generator

    string secret = "acckzz";
    vector<string> words = {"acckzz", "ccbazz", "eiowzz", "abcczz"};
    int allowedGuesses = 10;
    Master master(secret, words);
    findSecretWord(words, master, allowedGuesses);

    return 0;
}
