#include <string>
#include <vector>
#include <algorithm>

// error: passing ‘const std::string’ {aka ‘const std::__cxx11::basic_string<char>’} as ‘this’ argument discards qualifiers [-fpermissive]
//Removed const reference
// std::string high(const std::string& s) {
std::string high(std::string& s) {
    std::vector<std::string> words;
    size_t pos = 0;
    while ((pos = s.find(' ')) != std::string::npos) {
        words.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    words.push_back(s);
    std::string maxWord = "";
    int maxScore = 0;
    for (const auto& word : words) {
        int score = 0;
        for (char c : word) {
            score += c - 96;
        }
        if (score > maxScore) {
            maxScore = score;
            maxWord = word;
        }
    }
    return maxWord;
}