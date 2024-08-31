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

// #include "../../source/output/claude/cpp/Task35_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function
//#include "../../source/output/codestral/cpp/Task35_MISTRAL_codestral-latest.cpp"  // Include the header for the function
// #include "../../source/output/gemini/cpp/Task35_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function
 #include "../../source/output/gpt4o/cpp/Task35_OPENAI_gpt-4o.cpp"  // Include the header for the function
//#include "../../source/output/llama-3/cpp/Task35_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function



void testSingleStop() {
    // Test with only one stop where no one gets off
    std::vector<std::pair<int, int>> stops = {{10, 0}};
    assert(numberOfPeople(stops) == 10);
}

void testAllGetOff() {
    // Test where everyone gets off at the last stop
    std::vector<std::pair<int, int>> stops = {{10, 0}, {3, 5}, {2, 10}};
    assert(numberOfPeople(stops) == 0);
}

void testMoreGetOnThanOff() {
    // Test where more people get on the bus than get off at each stop
    std::vector<std::pair<int, int>> stops = {{5, 0}, {7, 3}, {4, 2}};
    assert(numberOfPeople(stops) == 11);
}

void testSamenumberOfPeopleGetOnAndOff() {
    // Test where the same numberOfPeople of people get on and off the bus at each stop
    std::vector<std::pair<int, int>> stops = {{3, 0}, {2, 2}, {0, 0}};
    assert(numberOfPeople(stops) == 3);
}

void testAllGetOnAtOnce() {
    // Test where all people get on at the first stop and none get off until the end
    std::vector<std::pair<int, int>> stops = {{20, 0}, {0, 0}, {0, 0}};
    assert(numberOfPeople(stops) == 20);
}

void testDecreasingPassengers() {
    // Test where the numberOfPeople of people decreases gradually
    std::vector<std::pair<int, int>> stops = {{10, 0}, {0, 3}, {0, 5}, {0, 2}};
    assert(numberOfPeople(stops) == 0);
}

void testEmptyBusStops() {
    // Test with stops that have zero people getting on and off
    std::vector<std::pair<int, int>> stops = {{10, 0}, {0, 0}, {0, 0}};
    assert(numberOfPeople(stops) == 10);
}

void testOnePersonLeft() {
    // Test where one person remains on the bus after all stops
    std::vector<std::pair<int, int>> stops = {{1, 0}, {0, 0}};
    assert(numberOfPeople(stops) == 1);
}

void testComplexScenario() {
    // Test with a complex scenario with varying numberOfPeoples
    std::vector<std::pair<int, int>> stops = {{10, 0}, {3, 5}, {5, 8}, {10, 2}, {0, 3}, {7, 3}};
    assert(numberOfPeople(stops) == 14);
}

void testLargenumberOfPeoples() {
    // Test with large numberOfPeoples
    std::vector<std::pair<int, int>> stops = {{1000, 0}, {500, 300}, {200, 200}, {300, 100}};
    assert(numberOfPeople(stops) == 1400);
}

int main() {
    // Running all test cases
    testSingleStop();
    testAllGetOff();
    testMoreGetOnThanOff();
    testSamenumberOfPeopleGetOnAndOff();
    testAllGetOnAtOnce();
    testDecreasingPassengers();
    testEmptyBusStops();
    testOnePersonLeft();
    testComplexScenario();
    testLargenumberOfPeoples();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}