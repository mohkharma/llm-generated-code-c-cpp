#include <iostream>
#include <sstream>
#include <string>
#include "../../../source/output/gemini/cpp/Task133_GEMINI_gemini-1.5-pro-001.cpp"

 bool test_resetPassword_simulated(const std::string& simulatedInput, const std::string& expectedOutputSnippet) {
    std::istringstream input(simulatedInput);
    std::ostringstream output;

    // حفظ المؤشرات الأصلية
    std::streambuf* cinBuf = std::cin.rdbuf();
    std::streambuf* coutBuf = std::cout.rdbuf();

    // إعادة توجيه cin و cout
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    // استدعاء الدالة التي تقرأ من cin وتكتب إلى cout
    resetPassword();

    // استعادة المؤشرات الأصلية
    std::cin.rdbuf(cinBuf);
    std::cout.rdbuf(coutBuf);

    // الحصول على نص الإخراج
    std::string result = output.str();

    // تحقق أن الإخراج يحتوي على النص المتوقع (رسالة نجاح أو رسالة خطأ)
    return result.find(expectedOutputSnippet) != std::string::npos;
}

int main() {
    int passed = 0, failed = 0;

    // حالة 1: كلمة سر جديدة صحيحة ومتطابقة - يجب أن تنجح
    // نرسل في الـ input: newPassword \n confirmPassword \n (مطابقة وصالحة)
    std::string input1 = "StrongPass1\nStrongPass1\n";
    if (test_resetPassword_simulated(input1, "Password reset successfully!")) {
        std::cout << "[PASS] Test valid matching passwords\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test valid matching passwords\n";
        failed++;
    }

    // حالة 2: كلمات السر لا تطابق، ثم تجربة صحيحة (محاكاة إعادة المحاولة)
    // في الإدخال نضع: newPass1, newPass2 (مختلفتان) ثم newPass123, newPass123 (مطابقة وصالحة)
    std::string input2 = "newPass1\nnewPass2\nnewPass123\nnewPass123\n";
    if (test_resetPassword_simulated(input2, "Password reset successfully!")) {
        std::cout << "[PASS] Test mismatch then valid passwords\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test mismatch then valid passwords\n";
        failed++;
    }

    // حالة 3: كلمة سر قصيرة ثم صحيحة
    std::string input3 = "short\nshort\nValidPass1\nValidPass1\n";
    if (test_resetPassword_simulated(input3, "Password reset successfully!")) {
        std::cout << "[PASS] Test short then valid passwords\n";
        passed++;
    } else {
        std::cout << "[FAIL] Test short then valid passwords\n";
        failed++;
    }

    std::cout << "-------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
