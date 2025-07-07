#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// The reverseWords function
std::string reverseWords(std::string s) {
    std::string word;
    std::vector<std::string> words;
    for (char c : s) {
        if (c == ' ') {
            if (word.length() >= 5) {
                std::reverse(word.begin(), word.end());
            }
            words.push_back(word);
            word = "";
        } else {
            word += c;
        }
    }
    if (word.length() >= 5) {
        std::reverse(word.begin(), word.end());
    }
    words.push_back(word);
    word = "";
    for (std::string w : words) {
        word += w + " ";
    }
    word.pop_back();
    return word;
}

// Test function to run test cases
void runTests() {
    bool passed = true;

    // Test Case 1: s = "Hey fellow warriors", Expected: "Hey wollef sroirraw"
    std::string test1 = "Hey fellow warriors";
    std::string expected1 = "Hey wollef sroirraw";
    std::string result1 = reverseWords(test1);
    std::cout << "Test Case 1: s = \"" << test1 << "\", Expected: \"" << expected1 << "\", Got: \"" << result1 << "\"";
    if (result1 == expected1) {
        std::cout << " -> Passed" << std::endl;
    } else {
        std::cout << " -> Failed" << std::endl;
        passed = false;
    }

    // Test Case 2: s = "This is a test", Expected: "This is a test"
    std::string test2 = "This is a test";
    std::string expected2 = "This is a test";
    std::string result2 = reverseWords(test2);
    std::cout << "Test Case 2: s = \"" << test2 << "\", Expected: \"" << expected2 << "\", Got: \"" << result2 << "\"";
    if (result2 == expected2) {
        std::cout << " -> Passed" << std::endl;
    } else {
        std::cout << " -> Failed" << std::endl;
        passed = false;
    }

    // Test Case 3: s = "This is another test", Expected: "This is rehtona test"
    std::string test3 = "This is another test";
    std::string expected3 = "This is rehtona test";
    std::string result3 = reverseWords(test3);
    std::cout << "Test Case 3: s = \"" << test3 << "\", Expected: \"" << expected3 << "\", Got: \"" << result3 << "\"";
    if (result3 == expected3) {
        std::cout << " -> Passed" << std::endl;
    } else {
        std::cout << " -> Failed" << std::endl;
        passed = false;
    }

    if (passed) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << "Some tests failed!" << std::endl;
    }
}

int main() {
    std::cout << "Running reverseWords Tests..." << std::endl;
    runTests();
    return 0;
}