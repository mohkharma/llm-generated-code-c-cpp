#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

// ✅ البرنامج الأصلي كما هو
int mainProgram() {
    std::string input_str;
    std::cin >> input_str;
    std::reverse(input_str.begin(), input_str.end());
    std::cout << input_str << std::endl;
    return 0;
}

// 🔧 إزالة \r في نهاية الأسطر (خاصة على Windows)
std::string normalize(const std::string& str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    return result;
}

// ✅ اختبار حالة واحدة
void runTest(const std::string& input, const std::string& expectedOutput) {
    std::stringstream in(input);
    std::stringstream out;

    // تبديل مؤقت لـ cin و cout
    std::streambuf* origCin = std::cin.rdbuf();
    std::streambuf* origCout = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // تشغيل البرنامج
    mainProgram();

    // استعادة cin و cout
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);

    // مقارنة الإخراج
    std::string actual = out.str();
    std::string expected = expectedOutput + "\n";

    if (normalize(actual) != normalize(expected)) {
        std::cerr << "❌ Test failed\n";
        std::cerr << "Input:    '" << input << "'\n";
        std::cerr << "Expected: '" << expected << "'\n";
        std::cerr << "Actual:   '" << actual << "'\n";
        assert(false);
    }
}

int main() {
    runTest("hello\n", "olleh");
    runTest("a\n", "a");
    runTest("madam\n", "madam");
    runTest("12345\n", "54321");
    runTest("!@#$%\n", "%$#@!");
    runTest("HeLLo\n", "oLLeH");
    runTest("abc def\n", "cba");  // فقط الكلمة الأولى تُقرأ
runTest("  test\n", "tset");
    runTest("\n", "");           // إدخال فارغ
    runTest("   \n", "");        // فراغات فقط

    std::cout << "\n✅ All test cases passed.\n";
    return 0;
}
