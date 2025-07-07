// Task184_Test.cpp

#include <iostream>
#include <string>
#include <set>
#include "../../../source/output/claude/cpp/Task184_CLAUDE_claude-3-5-sonnet-20240620.cpp"   

bool isValidNameFormat(const std::string& name) {
    if (name.length() != 5) return false;
    return std::isupper(name[0]) && std::isupper(name[1]) &&
           std::isdigit(name[2]) && std::isdigit(name[3]) && std::isdigit(name[4]);
}

int main() {
    bool allPassed = true;
    std::set<std::string> generatedNames;

    // Test 1: Creation produces valid name
    Robot r1;
    std::string name1 = r1.get_name();
    if (!isValidNameFormat(name1)) {
        std::cout << "❌ Test Case 1 Failed: Invalid name format: " << name1 << "\n";
        allPassed = false;
    }

    // Test 2: Name is unique
    if (generatedNames.find(name1) != generatedNames.end()) {
        std::cout << "❌ Test Case 2 Failed: Name already used: " << name1 << "\n";
        allPassed = false;
    }
    generatedNames.insert(name1);

    // Test 3: Reset produces new valid and unique name
    r1.reset();
    std::string name2 = r1.get_name();
    if (!isValidNameFormat(name2)) {
        std::cout << "❌ Test Case 3 Failed: Invalid name format after reset: " << name2 << "\n";
        allPassed = false;
    }
    if (name2 == name1) {
        std::cout << "❌ Test Case 4 Failed: Name did not change after reset.\n";
        allPassed = false;
    }
    if (generatedNames.find(name2) != generatedNames.end()) {
        std::cout << "❌ Test Case 5 Failed: New name after reset is not unique: " << name2 << "\n";
        allPassed = false;
    }
    generatedNames.insert(name2);

    // Test 4: Multiple robots produce unique names
    const int numRobots = 100;
    for (int i = 0; i < numRobots; ++i) {
        Robot r;
        std::string name = r.get_name();
        if (!isValidNameFormat(name)) {
            std::cout << "❌ Test Case 6 Failed: Invalid name format in batch: " << name << "\n";
            allPassed = false;
            break;
        }
        if (generatedNames.find(name) != generatedNames.end()) {
            std::cout << "❌ Test Case 7 Failed: Duplicate name in batch: " << name << "\n";
            allPassed = false;
            break;
        }
        generatedNames.insert(name);
    }

    if (allPassed) {
        std::cout << "✅ All test cases passed!\n";
    }

    return 0;
}
