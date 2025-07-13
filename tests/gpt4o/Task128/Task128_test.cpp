#define main mistral_main
#include "../../../source/output/gpt4o/cpp/Task128_OPENAI_gpt-4o.cpp"
#undef main

#include <iostream>
#include <sstream>
#include <string>

bool isWithinRange(int value, int min, int max) {
    return value >= min && value <= max;
}

int main() {
    std::cout << "=== Running Test for CPP Random Number Output ===\n";

    int passed = 0, total = 2;

    // إعادة توجيه الإخراج المؤقت
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    // تشغيل البرنامج الأصلي
    mistral_main();

    std::cout.rdbuf(oldCout);

    // قراءة السطر الكامل
    std::string label1, label2, colon;
    int value;
    buffer >> label1 >> label2 >> colon >> value;

    std::string combinedLabel = label1 + " " + label2;

    // Test 1: التأكد من صحة التنسيق
    if (combinedLabel == "CPP Random") {
        std::cout << "[PASS] Output label is correct\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Output label is incorrect: \"" << combinedLabel << "\"\n";
    }

    // Test 2: التحقق من المجال
    if (isWithinRange(value, 1, 100)) {
        std::cout << "[PASS] Random number is within range 1–100: " << value << "\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random number out of range: " << value << "\n";
    }

    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return passed == total ? 0 : 1;
}
