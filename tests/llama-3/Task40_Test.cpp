#include <iostream>
#include <sstream>
#include <string>
#include <cgicc/Cgicc.h>

#include "../../source/output/llama-3/cpp/Task40_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

int passed = 0;
int failed = 0;

void printResult(const std::string& name, bool success) {
    if (success) {
        std::cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << name << "\n";
        failed++;
    }
}

// وظيفة لمساعدة كل اختبار عبر إعادة توجيه cin + cout
std::string runWithSimulatedEnv(const std::string& method, const std::string& postData) {
    std::stringstream input(postData);
    std::stringstream output;

    // حفظ البيئة القديمة
    std::streambuf* cinBackup = std::cin.rdbuf();
    std::streambuf* coutBackup = std::cout.rdbuf();

    // ضبط البيئة
    setenv("REQUEST_METHOD", method.c_str(), 1);
    setenv("CONTENT_LENGTH", std::to_string(postData.length()).c_str(), 1);

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    // تشغيل الدالة
    handleSettingsForm();

    // استرجاع البيئة الأصلية
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    return output.str();
}

// ========== TESTS ==========

void test_1_render_form_includes_csrf() {
    std::string out = runWithSimulatedEnv("GET", "");
    bool ok = out.find("csrf_token") != std::string::npos &&
              out.find("random_token_here") != std::string::npos;
    printResult("test_1_render_form_includes_csrf", ok);
}

void test_2_accepts_valid_csrf_token() {
    std::string data = "csrf_token=random_token_here";
    std::string out = runWithSimulatedEnv("POST", data);
    bool ok = out.find("Settings updated successfully") != std::string::npos;
    printResult("test_2_accepts_valid_csrf_token", ok);
}

void test_3_rejects_invalid_csrf_token() {
    std::string data = "csrf_token=wrong_token";
    std::string out = runWithSimulatedEnv("POST", data);
    bool ok = out.find("CSRF token is invalid") != std::string::npos;
    printResult("test_3_rejects_invalid_csrf_token", ok);
}

void test_4_missing_csrf_token() {
    std::string data = "username=ali&email=a@example.com";
    std::string out = runWithSimulatedEnv("POST", data);
    bool ok = out.find("CSRF token is invalid") != std::string::npos;
    printResult("test_4_missing_csrf_token", ok);
}

// ========== MAIN ==========

int main() {
    test_1_render_form_includes_csrf();
    test_2_accepts_valid_csrf_token();
    test_3_rejects_invalid_csrf_token();
    test_4_missing_csrf_token();

    std::cout << "\nTests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
