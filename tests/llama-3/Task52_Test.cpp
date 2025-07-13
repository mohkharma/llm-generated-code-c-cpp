#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "../../source/output/llama-3/cpp/Task52_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

using namespace std;

bool fileExists(const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

string readFile(const string& filename) {
    ifstream file(filename);
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

int main() {
    const string testFile = "test_file.txt";
    int shift = 3;

    int testsPassed = 0;
    int testsFailed = 0;

    // Prepare test file
    {
        ofstream ofs(testFile);
        ofs << "Hello, World!";
    }

    // Test 1: Encrypt file (in-place)
    try {
        encryptFile(testFile, shift);

        if (!fileExists(testFile)) {
            cout << "Test 1 (encryptFile file exists): FAILED\n";
            ++testsFailed;
        } else {
            string encryptedContent = readFile(testFile);
            if (encryptedContent != "Khoor, Zruog!") {
                cout << "Test 1 (encryptFile content correctness): FAILED\n";
                cout << "Got: " << encryptedContent << "\n";
                ++testsFailed;
            } else {
                cout << "Test 1 (encryptFile): PASSED\n";
                ++testsPassed;
            }
        }
    } catch (...) {
        cout << "Test 1 (encryptFile exception): FAILED\n";
        ++testsFailed;
    }

    // Test 2: Decrypt file (in-place)
    try {
        decryptFile(testFile, shift);

        string decryptedContent = readFile(testFile);
        if (decryptedContent != "Hello, World!") {
            cout << "Test 2 (decryptFile content correctness): FAILED\n";
            cout << "Got: " << decryptedContent << "\n";
            ++testsFailed;
        } else {
            cout << "Test 2 (decryptFile): PASSED\n";
            ++testsPassed;
        }
    } catch (...) {
        cout << "Test 2 (decryptFile exception): FAILED\n";
        ++testsFailed;
    }

    // Cleanup
    remove(testFile.c_str());

    cout << "---------------------------------\n";
    cout << "Total tests passed: " << testsPassed << "\n";
    cout << "Total tests failed: " << testsFailed << "\n";

    return (testsFailed == 0) ? 0 : 1;
}
