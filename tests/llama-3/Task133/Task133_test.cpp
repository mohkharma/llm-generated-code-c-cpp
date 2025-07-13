#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/llama-3/cpp/Task133_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

bool test_resetPassword_simulated(const std::string& simulatedInput, const std::string& expectedOutputSnippet) {
    std::istringstream input(simulatedInput);
    std::ostringstream output;

    // حفظ مؤشرات الإدخال والإخراج الأصلية
    std::streambuf* cinBuf = std::cin.rdbuf();
    std::streambuf* coutBuf = std::cout.rdbuf();

    // إعادة توجيه cin و cout
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    resetPassword();

    // استعادة مؤشرات الإدخال والإخراج الأصلية
    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    std::string result = output.str();
    return result.find(expectedOutputSnippet) != std::string::npos;
}

int main() {
    int passed = 0, failed = 0;

    // حالة 1: تطابق كلمة السر الجديدة والتأكيد (يجب نجاح العملية)
    std::string input1 = "user1\noldpass\nnewpass123\nnewpass123\n";
    if (test_resetPassword_simulated(input1, "Password reset successfully!")) {
        std::cout << "[PASS] Test matching new passwords\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test matching new passwords\n";
        failed++;
    }

    // حالة 2: عدم تطابق كلمة السر الجديدة والتأكيد (يجب ظهور رسالة خطأ)
    std::string input2 = "user2\noldpass\nnewpass123\ndifferent123\n";
    if (test_resetPassword_simulated(input2, "New password and confirm password do not match")) {
        std::cout << "[PASS] Test non-matching new passwords\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test non-matching new passwords\n";
        failed++;
    }

    std::cout << "------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
