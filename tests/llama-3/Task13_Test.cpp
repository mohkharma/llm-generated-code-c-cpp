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

// #include "../../source/output/claude/cpp/Task13_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
// #include "../../source/output/codestral/cpp/Task12_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task12_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task12_OPENAI_gpt-4o.cpp"  // Include the header for the function
#include "../../source/output/llama-3/cpp/Task13_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


// Helper function to run and assert test cases
void assertTest(std::vector<std::string> walk, bool expected, const std::string &testName) {
    bool result = isValidWalk(walk);
    if (result == expected) {
        std::cout << "[PASS] " << testName << std::endl;
    } else {
        std::cout << "[FAIL] " << testName << ": Expected "" << expected << "", got "" << result << """ << std::endl;
    }
}

int main() {
    // Test cases
    assertTest({"n", "s", "n", "s", "n", "s", "n", "s", "n", "s"}, true, "testCase1");
    assertTest({"w", "e", "w", "e", "w", "e", "w", "e", "w", "e", "w", "e"}, false, "testCase2");
    assertTest({"w"}, false, "testCase3");
    assertTest({"n", "n", "n", "s", "n", "s", "n", "s", "n", "s"}, false, "testCase4");
    assertTest({"n", "s", "e", "w", "n", "s", "e", "w", "n", "s"}, true, "testCase5");
    assertTest({"n", "e", "s", "w", "n", "e", "s", "w", "n", "s"}, true, "testCase6");
    assertTest({"n", "n", "n", "n", "s", "s", "s", "s", "e", "w"}, true, "testCase7");
    assertTest({"n", "s", "n", "s", "e", "w", "e", "w", "n", "s"}, true, "testCase8");
    assertTest({"n", "n", "n", "n", "n", "n", "n", "n", "n", "n"}, false, "testCase9");
    assertTest({"n", "n", "e", "e", "s", "s", "w", "w", "n", "s"}, true, "testCase10");

    std::cout << "\nAll test cases completed." << std::endl;

    return 0;
}