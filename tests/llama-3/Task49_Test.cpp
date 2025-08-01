#include "../../source/output/llama-3/cpp/Task49_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>  // لإزالة الملفات

int main() {
    int passed = 0, failed = 0;

    // 🧹 تنظيف الملف السابق إن وُجد
    std::remove("users.txt");

    std::stringstream input("Test User\nuser@example.com\n");
    std::streambuf* orig_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::cout << "[TEST 1] test_store_user_in_file: ";
    try {
        storeUserInFile();

        // تحقق من أن السطر تمت إضافته إلى users.txt
        std::ifstream file("users.txt");
        std::string line;
        bool found = false;

        while (std::getline(file, line)) {
            if (line == "Test User,user@example.com") {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "PASSED\n";
            passed++;
        } else {
            std::cout << "FAILED (Entry not found in users.txt)\n";
            failed++;
        }
    } catch (...) {
        std::cout << "FAILED (Exception occurred)\n";
        failed++;
    }

    std::cin.rdbuf(orig_cin);  // استعادة cin الأصلي

    std::cout << "\n===== Test Summary =====\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
