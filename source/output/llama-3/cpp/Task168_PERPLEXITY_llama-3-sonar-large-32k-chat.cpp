#include <iostream>
#include <string>

std::string tweakLetters(std::string s, int tweaks[]) {
    std::string result = "";
    for (int i = 0; i < s.length(); i++) {
        char c = s[i] + tweaks[i];
        result += c;
    }
    return result;
}

int main() {
    //error: taking address of temporary array
    //fixed manually
    // std::cout << tweakLetters("apple", (int[]){0, 1, -1, 0, -1}) << std::endl; // "aqold"
    // std::cout << tweakLetters("many", (int[]){0, 0, 0, -1}) << std::endl; // "manx"
    // std::cout << tweakLetters("rhino", (int[]){1, 1, 1, 1, 1}) << std::endl; // "sijop"
    int x1 []  = {0, 1, -1, 0, -1};
    int x2 []  = {0, 0, 0, -1};
    int x3 []  = {1, 1, 1, 1, 1};
    std::cout << tweakLetters("apple", x1)<< std::endl; // "aqold"
    std::cout << tweakLetters("many", x2) << std::endl; // "manx"
    std::cout << tweakLetters("rhino", x3) << std::endl; // "sijop"
    return 0;
}