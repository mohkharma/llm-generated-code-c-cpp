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

// #include "../../source/output/claude/cpp/Task33_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
//#include "../../source/output/codestral/cpp/Task33_MISTRAL_codestral-latest.cpp"  // Include the header for the function
 #include "../../source/output/gemini/cpp/Task33_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
// #include "../../source/output/gpt4o/cpp/Task33_OPENAI_gpt-4o.cpp"  // Include the header for the function
//#include "../../source/output/llama-3/cpp/Task33_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function


void testSingleTill() {
    // All customers have to wait for the single till
    assert(queueTime({5, 3, 4}, 1) == 12);
}

void testTwoTills() {
    // The second till finishes before the first
    assert(queueTime({10, 2, 3, 3}, 2) == 10);
}

void testTwoTillsDifferentOrder() {
    // The tills have different workloads
    assert(queueTime({2, 3, 10}, 2) == 12);
}

void testMultipleTills() {
    // More tills than customers
    assert(queueTime({5, 3, 4}, 5) == 5);
}

void testEqualDistribution() {
    // Evenly distributed workload
    assert(queueTime({1, 2, 3, 4}, 2) == 6);
}

void testEmptyQueue() {
    // No customers
    assert(queueTime({}, 1) == 0);
}

void testOneCustomerMultipleTills() {
    // Single customer with multiple tills
    assert(queueTime({5}, 2) == 5);
}

void testLongQueue() {
    // Long queue of customers with minimal tills
    assert(queueTime({2, 2, 3, 3, 4, 4, 5, 5}, 1) == 28);
}

void testComplexDistribution() {
    // Complex distribution of customers
    assert(queueTime({2, 3, 4, 3, 2, 1}, 3) == 5);//
}

void testHighNumberOfTills() {
    // High number of tills, fewer customers
    assert(queueTime({1, 1, 1, 1, 1, 1}, 10) == 1);
}

int main() {
    // Running all test cases
    testSingleTill();
    testTwoTills();
    testTwoTillsDifferentOrder();
    testMultipleTills();
    testEqualDistribution();
    testEmptyQueue();
    testOneCustomerMultipleTills();
    testLongQueue();
    testComplexDistribution();
    testHighNumberOfTills();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}