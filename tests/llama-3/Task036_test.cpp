#include "../../source/output/codestral/cpp/Task36_MISTRAL_codestral-latest.cpp" // عدل حسب موقع الحل عندك

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
    string filename;           // ما ندخله إلى cin (بدون \n لأن >> يتجاهلها)
    string fileContent;        // محتوى الملف (فارغ = الملف غير موجود)
    string expectedOutput;     // الناتج المتوقع على cout
};

TestCase tests[] = {
    {"test_file.txt", "Hello, World!", "Enter file name: Hello, World!\n"},
    {"missing_file.txt", "", "Enter file name: Unable to open file"},
    {"test_file.txt", "", "Enter file name: Unable to open file"},
    {"content_file.txt", "File Content", "Enter file name: File Content\n"},
    {"empty_file.txt", "", "Enter file name: Unable to open file"},
    {"numeric_file.txt", "12345", "Enter file name: 12345\n"},
    {"special_chars.txt", "Special Characters !@#$%^&*()", "Enter file name: Special Characters !@#$%^&*()\n"},
    {"multiline_file.txt", "Line 1\nLine 2", "Enter file name: Line 1\nLine 2\n"}
};

int main() {
    cout << "Running strict Task36 Tests for readFileFromPrompt()...\n";

    IOInterceptor io;
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < total; ++i) {
        const auto& t = tests[i];

        // حذف الملف إذا موجود
        remove(t.filename.c_str());

        // إنشاء الملف إن كان هناك محتوى
        if (!t.fileContent.empty()) {
            ofstream f(t.filename);
            f << t.fileContent;
            f.close();
        }

        io.clearOutput();
        io.setInput(t.filename);  // إدخال اسم الملف بدون \n
        io.startCapture();

        readFileFromInput();

        io.stopCapture();

        string actualOutput = io.getOutput();

        bool pass = (actualOutput == t.expectedOutput);

        if (pass) {
            cout << "[PASS] Test " << (i+1) << " (" << t.filename << ")\n";
            ++passed;
        } else {
            cout << "[FAIL] Test " << (i+1) << " (" << t.filename << ")\n";
            cout << "  Expected output:\n---\n" << t.expectedOutput << "\n---\n";
            cout << "  Actual output:\n---\n" << actualOutput << "\n---\n";
        }

        // حذف الملف بعد الاختبار
        remove(t.filename.c_str());
    }

    cout << "-------------------------\n";
    cout << "Passed " << passed << " out of " << total << " tests.\n";

    return (passed == total) ? 0 : 1;
}
