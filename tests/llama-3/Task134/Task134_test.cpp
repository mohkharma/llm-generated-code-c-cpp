#include "../../../source/output/llama-3/cpp/Task134_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring> // for memcmp

using namespace std;

// دالة مساعدة لمقارنة سلسلتي نص/بايت بعرض نتيجة واضحة
bool compareBytes(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    return memcmp(a.data(), b.data(), a.size()) == 0;
}

int main() {
    bool all_passed = true;
    int test_count = 0;
    int passed_count = 0;

    // 1. اختبار توليد مفتاح وحفظه (لا يمكن حفظ ملف هنا، لذا نختبر فقط توليد المفتاح)
    test_count++;
    {
        KeyManager km;
        km.generateKey("secret.key");

        RSA* key = km.getKey("secret.key");
        if (key == nullptr) {
            cout << "[FAIL] Test " << test_count << ": generateKey and getKey - key is nullptr\n";
            all_passed = false;
        } else {
            cout << "[PASS] Test " << test_count << ": generateKey and getKey\n";
            passed_count++;
        }
    }

    // 2. اختبار hashKey يجب ان تعيد قيمة غير فارغة (نفس فكرة تشفير المفتاح)
    test_count++;
    {
        KeyManager km;
        km.generateKey("secret.key");
        string hash = km.hashKey("secret.key");
        if (hash.empty()) {
            cout << "[FAIL] Test " << test_count << ": hashKey - empty hash\n";
            all_passed = false;
        } else {
            cout << "[PASS] Test " << test_count << ": hashKey - non-empty hash\n";
            passed_count++;
        }
    }

    // 3. اختبار حذف المفتاح ثم التأكد انه غير موجود
    test_count++;
    {
        KeyManager km;
        km.generateKey("secret.key");
        km.deleteKey("secret.key");
        RSA* key = km.getKey("secret.key");
        if (key != nullptr) {
            cout << "[FAIL] Test " << test_count << ": deleteKey - key still exists\n";
            all_passed = false;
        } else {
            cout << "[PASS] Test " << test_count << ": deleteKey - key removed\n";
            passed_count++;
        }
    }

    // ملخص الاختبارات
    cout << "------------------------\n";
    cout << "Passed " << passed_count << " out of " << test_count << " tests.\n";

    if (all_passed) {
        cout << "All tests PASSED successfully.\n";
    } else {
        cout << "Some tests FAILED.\n";
    }

    return all_passed ? 0 : 1;
}
