#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <set>

#include "../../source/output/codestral/cpp/Task40_MISTRAL_codestral-latest.cpp"  // Include the header for the function

int passed = 0;
int failed = 0;

void printResult(const std::string& testName, bool success) {
    if (success) {
        std::cout << "[PASS] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

// ========== TEST CASES ==========

// 1. تأكد أن الرموز المُولدة مختلفة (عشوائية)
void test_generate_csrf_token_unique() {
    std::set<std::string> tokens;
    bool unique = true;
    for (int i = 0; i < 100; ++i) {
        std::string token = generate_csrf_token();
        if (tokens.count(token)) {
            unique = false;
            break;
        }
        tokens.insert(token);
    }
    printResult("test_generate_csrf_token_unique", unique);
}

// 2. تأكد أن الجلسة تولد وتحافظ على نفس الرمز طوال حياتها
void test_session_stores_token() {
    session s;
    std::string token1 = s.csrf_token();
    std::string token2 = s.csrf_token();
    printResult("test_session_stores_token", token1 == token2 && token1.length() > 0);
}

// 3. تأكد من أن update_settings يخزن الإعدادات بشكل صحيح
void test_update_settings_and_get() {
    session s;
    std::unordered_map<std::string, std::string> input = {
        {"setting1", "dark"},
        {"setting2", "enabled"}
    };
    s.update_settings(input);
    auto result = s.settings();
    bool ok = result["setting1"] == "dark" && result["setting2"] == "enabled";
    printResult("test_update_settings_and_get", ok);
}

// 4. تحقق أن رمز CSRF الخاطئ يتم رفضه
void test_invalid_csrf_rejected() {
    session_manager sm;
    auto sess = sm.get_session("abc123");

    std::unordered_map<std::string, std::string> new_settings = {
        {"setting1", "x"},
        {"setting2", "y"}
    };

    std::string fake_token = "invalid_token";

    // المقارنة اليدوية: هل يقبل الرمز الخاطئ؟
    bool allowed = (fake_token == sess->csrf_token());
    printResult("test_invalid_csrf_rejected", allowed == false);
}

// ========== MAIN ==========

int main() {
    test_generate_csrf_token_unique();
    test_session_stores_token();
    test_update_settings_and_get();
    test_invalid_csrf_rejected();

    std::cout << "\nTests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
