#define main mistral_main
#include "../../../source/output/gemini/cpp/Task128_GEMINI_gemini-1.5-pro-001.cpp"
#undef main

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <cstdlib>

bool isBetweenInt(int val, int min, int max) {
    return val >= min && val <= max;
}

bool isBetweenDouble(double val, double min, double max) {
    return val >= min && val <= max;
}

bool isValidFruit(const std::string& fruit) {
    return fruit == "apple" || fruit == "banana" || fruit == "cherry";
}

int main() {
    std::cout << "=== Running Tests for Random Integer, Double, and Fruit ===\n";

    int passed = 0, total = 3;

    // إعادة توجيه الإخراج المؤقتًا
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    // تشغيل البرنامج
    mistral_main();

    std::cout.rdbuf(oldCout);

    // قراءة النتائج من المخرجات
    std::string label1, label2, label3;
    int intVal;
    double doubleVal;
    std::string fruit;

    buffer >> label1 >> intVal;
    buffer >> label2 >> doubleVal;
    buffer >> label3 >> fruit;

    // Test 1: الرقم الصحيح بين 1 و 10
    if (isBetweenInt(intVal, 1, 10)) {
        std::cout << "[PASS] Random Integer in range 1–10\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random Integer out of range: " << intVal << "\n";
    }

    // Test 2: الرقم العشري بين 0.0 و 1.0
    if (isBetweenDouble(doubleVal, 0.0, 1.0)) {
        std::cout << "[PASS] Random Double in range 0.0–1.0\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Random Double out of range: " << doubleVal << "\n";
    }

    // Test 3: العنصر العشوائي من المصفوفة
    if (isValidFruit(fruit)) {
        std::cout << "[PASS] Random Fruit is valid: " << fruit << "\n";
        ++passed;
    } else {
        std::cout << "[FAIL] Invalid Fruit: " << fruit << "\n";
    }

    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return passed == total ? 0 : 1;
}
