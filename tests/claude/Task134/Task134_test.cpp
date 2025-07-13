#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include "../../../source/output/claude/cpp/Task134_CLAUDE_claude-3-5-sonnet-20240620.cpp"
// عدل المسار حسب موقع الحل عندك

// لأن الدوال في الحل تستخدم std::vector<unsigned char> لتمثيل المفتاح والرسالة المشفرة،
// ولأن التشفير باستخدام AES هنا بسيط وغير كامل (يشفّر بلوك واحد فقط، بدون وضع تشفير)،
//
// سنكتب اختبار مطابق للمنطق في بايثون:
// 1) إنشاء مفتاح عشوائي.
// 2) تشفير نص محدد "Hello, World!".
// 3) فك تشفير الناتج.
// 4) التأكد أن النص المفكوك يطابق النص الأصلي (مع التعامل مع null termination).
//
// ملاحظة: لأن الحل قد لا يضيف null terminator، سنقارن فقط أول n أحرف من النص المفكوك (حجم النص الأصلي).

bool test_crypto() {
    const std::string message = "Hello, World!";
    // توليد المفتاح
    std::vector<unsigned char> key = generate_key();

    // حفظ المفتاح في ملف ثم قراءته (اختبار وظيفي ل save_key و load_key)
    save_key(key, KEY_FILE);
    std::vector<unsigned char> loaded_key = load_key(KEY_FILE);

    // تحقق أن المفتاحين متطابقين
    if (key != loaded_key) {
        std::cerr << "[FAIL] Loaded key differs from saved key\n";
        return false;
    }

    // تشفير الرسالة
    std::vector<unsigned char> encrypted = encrypt_message(message, loaded_key);

    // فك التشفير
    std::string decrypted = decrypt_message(encrypted, loaded_key);

    // لأن النص المفكوك قد يحتوي على بيانات زائدة (ليس null-terminated)
    // نقارن فقط أول message.size() أحرف
    if (decrypted.size() < message.size()) {
        std::cerr << "[FAIL] Decrypted text shorter than original\n";
        return false;
    }

    if (std::memcmp(decrypted.data(), message.data(), message.size()) != 0) {
        std::cerr << "[FAIL] Decrypted text does not match original\n";
        return false;
    }

    return true;
}

int main() {
    int passed = 0, failed = 0;

    if (test_crypto()) {
        std::cout << "[PASS] Cryptographic key management test\n";
        passed++;
    } else {
        std::cout << "[FAIL] Cryptographic key management test\n";
        failed++;
    }

    std::cout << "--------------------------\n";
    std::cout << "Passed: " << passed << "\nFailed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
