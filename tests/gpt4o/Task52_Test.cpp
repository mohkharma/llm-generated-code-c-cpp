#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>

#include "../../source/output/gpt4o/cpp/Task52_OPENAI_gpt-4o.cpp"  // Include the header for the function

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

    // Create test input file
    {
        ofstream ofs(testFile, ios::binary);
        ofs << "Test content for AES encryption.";
    }

    // Generate a sample key vector of 16 bytes (AES 128-bit)
    vector<unsigned char> key(16);
    for (int i = 0; i < 16; ++i) {
        key[i] = static_cast<unsigned char>(i);
    }

    // Test 1: Encrypt file
    try {
        encryptFile(key, testFile, encryptedFile);
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
    } catch (...) {
        cout << "Test 1 (encryptFile exception): FAILED (exception thrown)\n";
        ++testsFailed;
    }

    // Test 2: Decrypt file
    try {
        decryptFile(key, encryptedFile, decryptedFile);
        if (!fileExists(decryptedFile)) {
            cout << "Test 2 (decryptFile output existence): FAILED\n";
            ++testsFailed;
        } else {
            ifstream original(testFile, ios::binary);
            ifstream decrypted(decryptedFile, ios::binary);

            string origContent((istreambuf_iterator<char>(original)), istreambuf_iterator<char>());
            string decContent((istreambuf_iterator<char>(decrypted)), istreambuf_iterator<char>());

            if (origContent == decContent) {
                cout << "Test 2 (decryptFile content correctness): PASSED\n";
                ++testsPassed;
            } else {
                cout << "Test 2 (decryptFile content correctness): FAILED (content mismatch)\n";
                ++testsFailed;
            }
        }
    } catch (...) {
        cout << "Test 2 (decryptFile exception): FAILED (exception thrown)\n";
        ++testsFailed;
    }

    // Test 3: Encrypt non-existent file
    try {
        encryptFile(key, "non_existent_file.txt", encryptedFile);
        if (!fileExists(encryptedFile)) {
            cout << "Test 3 (encryptFile non-existent input): PASSED (no output file)\n";
            ++testsPassed;
        } else {
            cout << "Test 3 (encryptFile non-existent input): FAILED (output file created)\n";
            ++testsFailed;
        }
    } catch (...) {
        cout << "Test 3 (encryptFile non-existent input): PASSED (exception thrown)\n";
        ++testsPassed;
    }

    // Test 4: Decrypt non-existent file
    try {
        decryptFile(key, "non_existent_file.encrypted", decryptedFile);
        if (!fileExists(decryptedFile)) {
            cout << "Test 4 (decryptFile non-existent input): PASSED (no output file)\n";
            ++testsPassed;
        } else {
            cout << "Test 4 (decryptFile non-existent input): FAILED (output file created)\n";
            ++testsFailed;
        }
    } catch (...) {
        cout << "Test 4 (decryptFile non-existent input): PASSED (exception thrown)\n";
        ++testsPassed;
    }

    // Cleanup test files
    remove(testFile.c_str());
    remove(encryptedFile.c_str());
    remove(decryptedFile.c_str());

    cout << "---------------------------------\n";
    cout << "Total tests passed: " << testsPassed << "\n";
    cout << "Total tests failed: " << testsFailed << "\n";

    return (testsFailed == 0) ? 0 : 1;
}
