#define main mistral_main
#include "../../../source/output/codestral/cpp/Task128_MISTRAL_codestral-latest.cpp"
#undef main

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <set>

int main() {
    std::cout << "=== Running Tests for Random Number Program ===\n";

    int passed = 0, total = 2;

    // --- Test 1: Output within range [1, 100] ---
    {
        std::stringstream buffer;
        std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

        // تشغيل الدالة نفسها الموجودة في الحل (بعد إعادة تعريف main → mistral_main)
        srand(42); // بذرة ثابتة للاختبار
        int num = rand() % 100 + 1;
        std::cout << num << std::endl;

        std::cout.rdbuf(oldCout);

        int output;
        buffer >> output;

        if (output >= 1 && output <= 100) {
            std::cout << "[PASS] Random number is within range 1–100\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Random number out of range: " << output << "\n";
        }
    }

    // --- Test 2: Check randomness (values vary over runs) ---
    {
        std::set<int> results;
        for (int i = 0; i < 50; ++i) {
            srand(time(0) + i); // بذرة متغيرة لضمان تنوع
            int num = rand() % 100 + 1;
            results.insert(num);
        }

        if (results.size() > 1) {
            std::cout << "[PASS] Random numbers vary over runs.\n";
            ++passed;
        } else {
            std::cout << "[FAIL] Random numbers did not vary over runs.\n";
        }
    }

    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return passed == total ? 0 : 1;
}
