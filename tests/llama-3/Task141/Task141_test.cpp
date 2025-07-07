#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <algorithm>

// ✅ البرنامج الفعلي كما هو
int mainProgram() {
    std::string s;
    std::cout << "Enter a string: ";
    std::getline(std::cin, s);
    std::string reversed = std::string(s.rbegin(), s.rend());
    std::cout << "Reversed string: " << reversed << std::endl;
    return 0;
}

// 🔧 إزالة \r في نهاية الأسطر (للتوافق مع Windows)
std::string normalize(const std::string& str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    return result;
}

// ✅ دالة تنفيذ اختبار واحد
void runTest(const std::string& input, const std::string& expectedReversedOutput) {
    std::stringstream in(input);
    std::stringstream out;

    // تبديل cin و cout مؤقتاً
    std::streambuf* origCin = std::cin.rdbuf();
    std::streambuf* origCout = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // تشغيل البرنامج
    mainProgram();

    // استرجاع cin و cout
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);

    std::string expected = "Enter a string: Reversed string: " + expectedReversedOutput + "\n";
    std::string actual = out.str();

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
    runTest("\n", "");
    runTest("a\n", "a");
    runTest("madam\n", "madam");
    runTest("hello world\n", "dlrow olleh");
    runTest("12345\n", "54321");
    runTest("!@#$%^&*()\n", ")(*&^%$#@!");
    runTest("HeLLo\n", "oLLeH");
    runTest("  hello  \n", "  olleh  ");
    runTest("abcdefghijklmnopqrstuvwxyz\n", "zyxwvutsrqponmlkjihgfedcba");

    std::cout << "\n✅ All test cases passed.\n";
    return 0;
}
