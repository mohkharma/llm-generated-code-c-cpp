#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <cstring>

#include "../../source/output/gemini/cpp/Task52_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

using namespace std;

bool fileExists(const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

bool filesAreDifferent(const string& file1, const string& file2) {
    ifstream f1(file1, ios::binary);
    ifstream f2(file2, ios::binary);

    if (!f1.is_open() || !f2.is_open()) return false;

    f1.seekg(0, ios::end);
    f2.seekg(0, ios::end);
    if (f1.tellg() != f2.tellg()) return true;

    f1.seekg(0, ios::beg);
    f2.seekg(0, ios::beg);

    const size_t bufferSize = 4096;
    char buf1[bufferSize];
    char buf2[bufferSize];

    while (f1.read(buf1, bufferSize) && f2.read(buf2, bufferSize)) {
        if (memcmp(buf1, buf2, bufferSize) != 0) return true;
    }
    if (f1.gcount() != f2.gcount()) return true;
    if (memcmp(buf1, buf2, f1.gcount()) != 0) return true;

    return false;
}

int main() {
    const string testFile = "test_file.txt";
    const string encryptedFile = testFile + ".encrypted";
    const string decryptedFile = testFile + ".decrypted";

    int testsPassed = 0;
    int testsFailed = 0;

    // إنشاء ملف الاختبار
    {
        ofstream ofs(testFile, ios::binary);
        ofs << "This is a test for AES encryption.";
    }

    // توليد مفتاح عشوائي
    vector<unsigned char> key = generateKey();

    // اختبار 1: التشفير
    if (encryptFile(testFile, encryptedFile, key)) {
        if (!fileExists(encryptedFile)) {
            cout << "Test 1 (encryptFile output existence): FAILED\n";
            ++testsFailed;
        } else if (filesAreDifferent(testFile, encryptedFile)) {
            cout << "Test 1 (encryptFile content difference): PASSED\n";
            ++testsPassed;
        } else {
            cout << "Test 1 (encryptFile content difference): FAILED (files identical)\n";
            ++testsFailed;
        }
    } else {
        cout << "Test 1 (encryptFile returned false): FAILED\n";
        ++testsFailed;
    }

    // اختبار 2: فك التشفير
    if (decryptFile(encryptedFile, decryptedFile, key)) {
        if (!fileExists(decryptedFile)) {
            cout << "Test 2 (decryptFile output existence): FAILED\n";
            ++testsFailed;
        } else {
            // قراءة الملفات للمقارنة
            ifstream original(testFile, ios::binary);
            ifstream decrypted(decryptedFile, ios::binary);

            string origContent((istreambuf_iterator<char>(original)), istreambuf_iterator<char>());
            string decContent((istreambuf_iterator<char>(decrypted)), istreambuf_iterator<char>());

            // إزالة الحشو الصفري من نهاية المحتوى المفكوك
            while (!decContent.empty() && decContent.back() == '\0')
                decContent.pop_back();

            if (origContent == decContent) {
                cout << "Test 2 (decryptFile content correctness): PASSED\n";
                ++testsPassed;
            } else {
                cout << "Test 2 (decryptFile content correctness): FAILED (content mismatch)\n";
                ++testsFailed;
            }
        }
    } else {
        cout << "Test 2 (decryptFile returned false): FAILED\n";
        ++testsFailed;
    }

    // اختبار 3: تشفير ملف غير موجود (نتوقع فشل العملية وعدم إنشاء ملف)
    if (!encryptFile("non_existent_input.txt", encryptedFile, key)) {
        if (!fileExists(encryptedFile)) {
            cout << "Test 3 (encryptFile non-existent input): PASSED (no output file)\n";
            ++testsPassed;
        } else {
            cout << "Test 3 (encryptFile non-existent input): FAILED (output file created)\n";
            ++testsFailed;
        }
    } else {
        cout << "Test 3 (encryptFile non-existent input returned true): FAILED\n";
        ++testsFailed;
    }

    // اختبار 4: فك التشفير لملف غير موجود (نتوقع فشل وعدم إنشاء ملف)
    if (!decryptFile("non_existent_input.encrypted", decryptedFile, key)) {
        if (!fileExists(decryptedFile)) {
            cout << "Test 4 (decryptFile non-existent input): PASSED (no output file)\n";
            ++testsPassed;
        } else {
            cout << "Test 4 (decryptFile non-existent input): FAILED (output file created)\n";
            ++testsFailed;
        }
    } else {
        cout << "Test 4 (decryptFile non-existent input returned true): FAILED\n";
        ++testsFailed;
    }

    // تنظيف الملفات
    remove(testFile.c_str());
    remove(encryptedFile.c_str());
    remove(decryptedFile.c_str());

    cout << "---------------------------------\n";
    cout << "Total tests passed: " << testsPassed << "\n";
    cout << "Total tests failed: " << testsFailed << "\n";

    return (testsFailed == 0) ? 0 : 1;
}
