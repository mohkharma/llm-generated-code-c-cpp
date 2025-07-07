#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

// ✅ البرنامج المراد اختباره
int mainProgram() {
    std::string str;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);

    std::reverse(str.begin(), str.end());

    std::cout << str << std::endl;
    return 0;
}

// ✅ دالة تشغيل اختبار واحد
void runTest(const std::string& input, const std::string& expectedOutput) {
    std::stringstream in(input);
    std::stringstream out;

    // حفظ الإدخال والإخراج الأصليين
    std::streambuf* origCin = std::cin.rdbuf();
    std::streambuf* origCout = std::cout.rdbuf();

    // تبديل مؤقت لـ cin و cout
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // تشغيل البرنامج
    mainProgram();

    // استعادة cin و cout
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);

    // التحقق من الإخراج الكامل
    std::string expected = "Enter a string: " + expectedOutput + "\n";
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
