#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

//#include "../../source/output/claude/cpp/Task23_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task23_MISTRAL_codestral-latest.cpp"  // Include the header for the function
 #include "../../source/output/gemini/cpp/Task23_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task23_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task23_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function



int main() {
    // Test Case 1
    long long m1 = 1071225;
    long long expected1 = 45;
    assert(ASum::findNb(m1) == expected1);
    std::cout << "Test Case 1 passed!" << std::endl;

    // Test Case 2
    long long m2 = 91716553919377LL;
    long long expected2 = -1;
    assert(ASum::findNb(m2) == expected2);
    std::cout << "Test Case 2 passed!" << std::endl;

    // Test Case 3
    long long m3 = 1;
    long long expected3 = 1;
    assert(ASum::findNb(m3) == expected3);
    std::cout << "Test Case 3 passed!" << std::endl;

    // Test Case 4
    long long m4 = 9;
    long long expected4 = 2;
    assert(ASum::findNb(m4) == expected4);
    std::cout << "Test Case 4 passed!" << std::endl;

    // Test Case 5
    long long m5 = 36;
    long long expected5 = 3;
    assert(ASum::findNb(m5) == expected5);
    std::cout << "Test Case 5 passed!" << std::endl;

    // Test Case 6
    long long m6 = 1000;
    long long expected6 = -1;///////// todo java and python
    assert(ASum::findNb(m6) == expected6);
    std::cout << "Test Case 6 passed!" << std::endl;

    // Test Case 7
    long long m7 = 2025;
    long long expected7 = 9;////////// todo java and python
    assert(ASum::findNb(m7) == expected7);
    std::cout << "Test Case 7 passed!" << std::endl;

    // Test Case 8
    long long m8 = 1000000;
    long long expected8 = -1;////////// todo java and python
    assert(ASum::findNb(m8) == expected8);
    std::cout << "Test Case 8 passed!" << std::endl;

    // Test Case 9
    long long m9 = 2552550;
    long long expected9 = -1;
    assert(ASum::findNb(m9) == expected9);
    std::cout << "Test Case 9 passed!" << std::endl;

    // Test Case 10
    long long m10 = 3375;
    long long expected10 = -1;/////// todo java and python
    assert(ASum::findNb(m10) == expected10);
    std::cout << ASum::findNb(m10)<< std::endl;

    std::cout << "All test cases passed!" << std::endl;

    return 0;
}