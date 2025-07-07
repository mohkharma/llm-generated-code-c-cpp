// Task184_Test.cpp

#include <iostream>
#include <string>
#include <set>
#include "../../../source/output/gemini/cpp/Task184_GEMINI_gemini-1.5-pro-001.cpp"

bool isValidNameFormat(const std::string& name) {
    if (name.length() != 5) return false;
    return std::isupper(name[0]) && std::isupper(name[1]) &&
           std::isdigit(name[2]) && std::isdigit(name[3]) && std::isdigit(name[4]);
}

int main() {
    bool allPassed = true;
    std::set<std::string> usedNames;

    // Test 1: First name is valid format
    Robot r1;
    std::string name1 = r1.getName();
    if (!isValidNameFormat(name1)) {
        std::cout << "❌ Test Case 1 Failed: Invalid name format: " << name1 << "\n";
        allPassed = false;
    }
    usedNames.insert(name1);

    // Test 2: Reset should generate new name
    r1.reset();
    std::string name2 = r1.getName();
    if (!isValidNameFormat(name2)) {
        std::cout << "❌ Test Case 2 Failed: Invalid name format after reset: " << name2 << "\n";
        allPassed = false;
    }
    if (name1 == name2) {
        std::cout << "❌ Test Case 3 Failed: Name did not change after reset.\n";
        allPassed = false;
    }
    if (usedNames.find(name2) != usedNames.end()) {
        std::cout << "❌ Test Case 4 Failed: Name after reset is not unique: " << name2 << "\n";
        allPassed = false;
    }
    usedNames.insert(name2);

    // Test 3: 1000 robots must all have unique names
    for (int i = 0; i < 1000; ++i) {
        Robot r;
        std::string name = r.getName();
        if (!isValidNameFormat(name)) {
            std::cout << "❌ Test Case 5 Failed: Invalid format in batch: " << name << "\n";
            allPassed = false;
            break;
        }
        if (usedNames.find(name) != usedNames.end()) {
            std::cout << "❌ Test Case 6 Failed: Duplicate name in batch: " << name << "\n";
            allPassed = false;
            break;
        }
        usedNames.insert(name);
    }

    if (allPassed) {
        std::cout << "✅ All test cases passed!\n";
    }

    return 0;
}
