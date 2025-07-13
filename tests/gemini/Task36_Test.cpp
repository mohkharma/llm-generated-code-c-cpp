#include "../../source/output/gemini/cpp/Task36_GEMINI_gemini-1.5-pro-001.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

class IOInterceptor {
    streambuf* oldCin;
    streambuf* oldCout;

    istringstream inputBuffer;
    ostringstream outputBuffer;

public:
    void setInput(const string& input) {
        inputBuffer.str(input);
        inputBuffer.clear();
    }

    void startCapture() {
        oldCin = cin.rdbuf(inputBuffer.rdbuf());
        oldCout = cout.rdbuf(outputBuffer.rdbuf());
    }

    void stopCapture() {
        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);
    }

    string getOutput() const {
        return outputBuffer.str();
    }

    void clearOutput() {
        outputBuffer.str("");
        outputBuffer.clear();
    }
};

struct TestCase {
    string inputFileName;       // ما ندخله لـ cin (اسم الملف فقط بدون \n لأن >> يتجاهل المساحات)
    string fileContent;         // محتوى الملف الحقيقي (فارغ = ملف غير موجود)
    string expectedOutput;      // الناتج المتوقع على cout (يشمل طلب الإدخال تماماً)
};

TestCase tests[] = {
    {"test_file.txt", "Hello, World!", "Enter the file name: Hello, World!\n"},
    {"missing_file.txt", "", "Enter the file name: Error: File not found.\n"},
    {"test_file.txt", "", "Enter the file name: Error: File not found.\n"},
    {"content_file.txt", "File Content", "Enter the file name: File Content\n"},
    {"empty_file.txt", "", "Enter the file name: Error: File not found.\n"},
    {"numeric_file.txt", "12345", "Enter the file name: 12345\n"},
    {"special_chars.txt", "Special Characters !@#$%^&*()", "Enter the file name: Special Characters !@#$%^&*()\n"},
    {"multiline_file.txt", "Line 1\nLine 2", "Enter the file name: Line 1\nLine 2\n"}
};

int main() {
    cout << "Running strict Task36 Tests for readFileInteractive()...\n";

    IOInterceptor io;
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < total; ++i) {
        const auto& t = tests[i];

        remove(t.inputFileName.c_str());

        if (!t.fileContent.empty()) {
            ofstream f(t.inputFileName);
            f << t.fileContent;
            f.close();
        }

        io.clearOutput();
        io.setInput(t.inputFileName); // بدون \n لأن >> يتجاهلها
        io.startCapture();

        readFileInteractive();

        io.stopCapture();

        string actualOutput = io.getOutput();

        bool pass = (actualOutput == t.expectedOutput);

        if (pass) {
            cout << "[PASS] Test " << (i+1) << " (" << t.inputFileName << ")\n";
            ++passed;
        } else {
            cout << "[FAIL] Test " << (i+1) << " (" << t.inputFileName << ")\n";
            cout << "  Expected output:\n---\n" << t.expectedOutput << "\n---\n";
            cout << "  Actual output:\n---\n" << actualOutput << "\n---\n";
        }

        remove(t.inputFileName.c_str());
    }

    cout << "-------------------------\n";
    cout << "Passed " << passed << " out of " << total << " tests.\n";

    return (passed == total) ? 0 : 1;
}
