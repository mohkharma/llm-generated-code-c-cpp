// Task184_Test.cpp

#include <iostream>
#include <string>
#include <set>
#include "../../../source/output/codestral/cpp/Task184_MISTRAL_codestral-latest.cpp"

bool isValidNameFormat(const std::string& name) {
    if (name.length() != 5) return false;
    return std::isupper(name[0]) && std::isupper(name[1]) &&
           std::isdigit(name[2]) && std::isdigit(name[3]) && std::isdigit(name[4]);
}

int main() {
    bool allPassed = true;
    std::set<std::string> usedNames;

    // Test 1: Single robot name validity
    Robot r1;
    std::string name1 = r1.getName();
    if (!isValidNameFormat(name1)) {
        std::cout << "❌ Test Case 1 Failed: Invalid name format: " << name1 << "\n";
        allPassed = false;
    }
    usedNames.insert(name1);

    // Test 2: Generate multiple unique names
    for (int i = 0; i < 1000; ++i) {
        Robot r;
        std::string name = r.getName();
        if (!isValidNameFormat(name)) {
            std::cout << "❌ Test Case 2 Failed: Invalid name format: " << name << "\n";
            allPassed = false;
            break;
        }
        if (usedNames.find(name) != usedNames.end()) {
            std::cout << "❌ Test Case 3 Failed: Duplicate name: " << name << "\n";
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
