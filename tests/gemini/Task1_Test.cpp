#include <iostream>
#include <vector>
#include <cassert>
#include "../../source/output/claude/cpp/Task1_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

void testNumberOfPeopleOnBus() {
    // Test Case 1: Basic scenario with a few stops
    std::vector<std::pair<int, int>> stops1 = { {3, 0}, {2, 1}, {5, 2}, {1, 4} };
    assert(numberOfPeopleOnBus(stops1) == 4);

    // Test Case 2: More people get off than get on at some stops
    std::vector<std::pair<int, int>> stops2 = { {10, 0}, {3, 5}, {2, 1}, {7, 10} };
    assert(numberOfPeopleOnBus(stops2) == 6);

    // Test Case 3: No people getting on or off the bus
    std::vector<std::pair<int, int>> stops3 = { {0, 0}, {0, 0}, {0, 0}, {0, 0} };
    assert(numberOfPeopleOnBus(stops3) == 0);

    // Test Case 4: Mixed scenario with various numbers of people
    std::vector<std::pair<int, int>> stops4 = { {5, 0}, {3, 2}, {8, 4}, {2, 1} };
    assert(numberOfPeopleOnBus(stops4) == 11);

    // Test Case 5: Some stops with no changes
    std::vector<std::pair<int, int>> stops5 = { {7, 0}, {0, 0}, {5, 3}, {3, 7}, {4, 0} };
    assert(numberOfPeopleOnBus(stops5) == 9);

    // Test Case 6: Balancing out to zero at some stops
    std::vector<std::pair<int, int>> stops6 = { {1, 0}, {0, 0}, {1, 1}, {0, 0}, {1, 0}, {0, 1} };
    assert(numberOfPeopleOnBus(stops6) == 1);

    // Test Case 7: Handling large numbers
    std::vector<std::pair<int, int>> stops7 = { {100, 0}, {50, 30}, {25, 25}, {10, 15}, {0, 10} };
    assert(numberOfPeopleOnBus(stops7) == 105);

    // Test Case 8: Different numbers of people getting on and off
    std::vector<std::pair<int, int>> stops8 = { {3, 0}, {0, 2}, {2, 1}, {0, 1}, {1, 0} };
    assert(numberOfPeopleOnBus(stops8) == 2);

    // Test Case 9: Bus ends up empty after the final stop
    std::vector<std::pair<int, int>> stops9 = { {50, 0}, {0, 50} };
    assert(numberOfPeopleOnBus(stops9) == 0);

    // Test Case 10: Varied inputs with different stop values
    std::vector<std::pair<int, int>> stops10 = { {6, 0}, {2, 3}, {1, 5}, {7, 2} };
    assert(numberOfPeopleOnBus(stops10) == 6);
}

int main() {
    testNumberOfPeopleOnBus();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
