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

#include "../../source/output/claude/cpp/Task15_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task15_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task15_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task15_OPENAI_gpt-4o.cpp"  // Include the header for the function
// #include "../../source/output/llama-3/cpp/Task15_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

int main() {
    auto tower1 = towerBuilder(1);
    for (const auto& floor : tower1) {
        std::cout << floor << std::endl;
    }
    std::cout << std::endl;

    auto tower2 = towerBuilder(2);
    for (const auto& floor : tower2) {
        std::cout << floor << std::endl;
    }
    auto tower5 = towerBuilder(5);
    for (const auto& floor : tower5) {
        std::cout << floor << std::endl;
    }
    auto tower7 = towerBuilder(7);
    for (const auto& floor : tower7) {
        std::cout << floor << std::endl;
    }
    auto tower9 = towerBuilder(9);
    for (const auto& floor : tower9) {
        std::cout << floor << std::endl;
    }


    return 0;
}