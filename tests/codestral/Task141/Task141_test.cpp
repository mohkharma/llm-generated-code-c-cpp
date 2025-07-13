#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

// ✅ كود الحل المُراد اختباره
int mainProgram() {
    std::string inputString;
    std::cout << "Enter a string: ";
    std::getline(std::cin, inputString);
    std::reverse(inputString.begin(), inputString.end());
    std::cout << "Reversed string is: " << inputString;
    return 0;
}

// ✅ دالة اختبار واحدة لكل حالة
void runTest(const std::string& input, const std::string& expectedOutput) {
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

    // تكوين الإخراج المتوقع
    std::string expected = "Enter a string: Reversed string is: " + expectedOutput;

    // التحقق من النتيجة
    std::string actual = out.str();
    assert(actual == expected && "❌ Test failed");
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
