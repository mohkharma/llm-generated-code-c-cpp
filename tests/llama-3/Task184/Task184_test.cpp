// Task184_Test.cpp

#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "../../../source/output/llama-3/cpp/Task184_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
bool isValidNameFormat(const std::string& name) {
    if (name.length() < 3 || name.length() > 5) return false;
    if (!std::isupper(name[0]) || !std::isupper(name[1])) return false;
    for (size_t i = 2; i < name.size(); ++i) {
        if (!std::isdigit(name[i])) return false;
    }
    return true;
}

int main() {
    bool allPassed = true;
    std::set<std::string> used;

     Robot r1;
    std::string name1 = r1.getName();
    if (!isValidNameFormat(name1)) {
        std::cout << "❌ Test 1 Failed: Invalid name format: " << name1 << "\n";
        allPassed = false;
    }
    used.insert(name1);

     r1.reset();
    std::string name2 = r1.getName();
    if (!isValidNameFormat(name2)) {
        std::cout << "❌ Test 2 Failed: Invalid name format after reset: " << name2 << "\n";
        allPassed = false;
    }
    if (name2 == name1) {
        std::cout << "❌ Test 3 Failed: Name did not change after reset.\n";
        allPassed = false;
    }
    if (used.find(name2) != used.end()) {
        std::cout << "❌ Test 4 Failed: Name after reset is not unique: " << name2 << "\n";
        allPassed = false;
    }
    used.insert(name2);

     for (int i = 0; i < 1000; ++i) {
        Robot r;
        std::string name = r.getName();
        if (!isValidNameFormat(name)) {
            std::cout << "❌ Test 5 Failed: Invalid format in batch: " << name << "\n";
            allPassed = false;
            break;
        }
        if (!used.insert(name).second) {
            std::cout << "❌ Test 6 Failed: Duplicate name in batch: " << name << "\n";
            allPassed = false;
            break;
        }
    }

    if (allPassed) {
        std::cout << "✅ All test cases passed!\n";
    }

    return 0;
}
