#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

// ✅ الحل المُراد اختباره
std::string reverseString(std::string s) {
    std::reverse(s.begin(), s.end());
    return s;
}

void runTest(const std::string& input, const std::string& expectedOutput) {
    std::stringstream in(input);
    std::stringstream out;

    // محاكاة std::cin و std::cout
    std::streambuf* origCin = std::cin.rdbuf();
    std::streambuf* origCout = std::cout.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    // تنفيذ البرنامج
    std::string inputStr;
    std::cout << "Enter a string: ";
    std::getline(std::cin, inputStr);
    std::cout << "Reversed string: " << reverseString(inputStr) << std::endl;

    // استرجاع std::cin و std::cout
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);

    // استخراج الناتج بدون البادئة
    std::string expectedFullOutput = "Enter a string: Reversed string: " + expectedOutput + "\n";
    std::string actualOutput = out.str();

    // تأكيد الناتج
    assert(actualOutput == expectedFullOutput && "❌ Test failed");
}

int main() {
    runTest("hello", "olleh");
    runTest("", "");
    runTest("a", "a");
    runTest("madam", "madam");
    runTest("hello world", "dlrow olleh");
    runTest("12345", "54321");
    runTest("!@#$%^&*()", ")(*&^%$#@!");
    runTest("HeLLo", "oLLeH");
    runTest("  hello  ", "  olleh  ");
    runTest("abcdefghijklmnopqrstuvwxyz", "zyxwvutsrqponmlkjihgfedcba");

    std::cout << "✅ All test cases passed.\n";
    return 0;
}
