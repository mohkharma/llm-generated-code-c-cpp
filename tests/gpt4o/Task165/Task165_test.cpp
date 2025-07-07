#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>

bool checkFlush(std::vector<std::string> table, std::vector<std::string> hand) {
    std::unordered_map<char, int> suits = {{'S', 0}, {'H', 0}, {'D', 0}, {'C', 0}};

    for (const std::string& card : table) {
        suits[card.back()]++;
    }

    for (const std::string& card : hand) {
        suits[card.back()]++;
    }

    for (const auto& suit : suits) {
        if (suit.second >= 5) return true;
    }

    return false;
}

void runTest(const std::vector<std::string>& table, const std::vector<std::string>& hand, bool expected, const char* testName) {
    bool result = checkFlush(table, hand);
    assert(result == expected && testName);
}

int main() {
    runTest({"A_S", "J_H", "7_D", "8_D", "10_D"}, {"J_D", "3_D"}, true, "test_case_1");
    runTest({"10_S", "7_S", "9_H", "4_S", "3_S"}, {"K_S", "Q_S"}, true, "test_case_2");
    runTest({"3_S", "10_H", "10_D", "10_C", "10_S"}, {"3_S", "4_D"}, false, "test_case_3");
    runTest({"2_H", "3_H", "4_H", "5_H", "6_D"}, {"7_H", "8_H"}, true, "test_case_4");
    runTest({"9_S", "8_H", "7_D", "6_C", "5_S"}, {"4_D", "3_H"}, false, "test_case_5");
    runTest({"K_C", "Q_C", "J_C", "9_C", "2_H"}, {"8_C", "7_C"}, true, "test_case_6");
    runTest({"A_S", "2_S", "3_S", "4_H", "5_H"}, {"6_S", "7_H"}, false, "test_case_7");
    runTest({"2_D", "3_D", "4_D", "5_D", "6_D"}, {"7_H", "8_H"}, true, "test_case_8");
    runTest({"A_S", "K_H", "Q_D", "J_C", "10_S"}, {"9_H", "8_C"}, false, "test_case_9");
    runTest({"A_S", "K_S", "Q_S", "J_S", "10_S"}, {"9_S", "8_S"}, true, "test_case_10");

    std::cout << "ALL GOOD\n";
    return 0;
}
