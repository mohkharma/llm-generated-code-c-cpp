// Task184_Test.cpp

#include <iostream>
#include <string>
#include <set>
#include "../../../source/output/gpt4o/cpp/Task184_OPENAI_gpt-4o.cpp"

bool isValidNameFormat(const std::string& name) {
    return name.length() == 5 &&
           std::isupper(name[0]) && std::isupper(name[1]) &&
           std::isdigit(name[2]) && std::isdigit(name[3]) && std::isdigit(name[4]);
}

int main() {
    bool allPassed = true;
    std::set<std::string> seen;

     Robot r1;
    std::string name1 = r1.getName();
    if (!isValidNameFormat(name1)) {
        std::cout << "❌ Test Case 1 Failed: Invalid format: " << name1 << "\n";
        allPassed = false;
    }
    seen.insert(name1);

     r1.reset();
    std::string name2 = r1.getName();
    if (!isValidNameFormat(name2)) {
        std::cout << "❌ Test Case 2 Failed: Invalid format after reset: " << name2 << "\n";
        allPassed = false;
    }
    if (name1 == name2) {
        std::cout << "❌ Test Case 3 Failed: Name did not change after reset.\n";
        allPassed = false;
    }
    if (seen.find(name2) != seen.end()) {
        std::cout << "❌ Test Case 4 Failed: Name after reset is not unique: " << name2 << "\n";
        allPassed = false;
    }
    seen.insert(name2);

     for (int i = 0; i < 1000; ++i) {
        Robot r;
        std::string name = r.getName();
        if (!isValidNameFormat(name)) {
            std::cout << "❌ Test Case 5 Failed: Invalid name format in batch: " << name << "\n";
            allPassed = false;
            break;
        }
        if (seen.find(name) != seen.end()) {
            std::cout << "❌ Test Case 6 Failed: Duplicate name: " << name << "\n";
            allPassed = false;
            break;
        }
        seen.insert(name);
    }

    if (allPassed) {
        std::cout << "✅ All test cases passed!\n";
    }

    return 0;
}
