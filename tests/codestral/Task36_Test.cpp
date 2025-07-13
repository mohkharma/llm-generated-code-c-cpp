#include "../../source/output/codestral/cpp/Task36_MISTRAL_codestral-latest.cpp"  // غير المسار حسب موقع الحل عندك

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
    string inputFileName;       // القيمة التي نرسلها لـ cin (اسم الملف مع \n)
    string fileContent;         // محتوى الملف الحقيقي (فارغ = ملف غير موجود)
    string expectedOutput;      // الناتج المتوقع على cout، يجب مطابقته حرفيًا مع اختبار Python
};

// طبقنا بالضبط 8 اختبارات Python الأصلية، نفس المدخلات والنواتج
TestCase tests[] = {
    {"test_file.txt\n", "Hello, World!", "Enter file name: Hello, World!\n"},
    {"missing_file.txt\n", "", "Enter file name: Unable to open file"},
    {"test_file.txt\n", "", "Enter file name: Unable to open file"},  // محاكاة IOError بالملف الفارغ
    {"content_file.txt\n", "File Content", "Enter file name: File Content\n"},
    {"empty_file.txt\n", "", "Enter file name: Unable to open file"},
    {"numeric_file.txt\n", "12345", "Enter file name: 12345\n"},
    {"special_chars.txt\n", "Special Characters !@#$%^&*()", "Enter file name: Special Characters !@#$%^&*()\n"},
    {"multiline_file.txt\n", "Line 1\nLine 2", "Enter file name: Line 1\nLine 2\n"}
};

int main() {
    cout << "Running strict Task36 Tests...\n";

    IOInterceptor io;
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < total; ++i) {
        const auto& t = tests[i];

        // حذف الملف إن وجد
        remove(t.inputFileName.c_str());

        // إذا محتوى الملف غير فارغ، ننشئه
        if (!t.fileContent.empty()) {
            ofstream f(t.inputFileName.substr(0, t.inputFileName.size() - 1)); // نحذف \n
            f << t.fileContent;
            f.close();
        }

        io.clearOutput();
        io.setInput(t.inputFileName);
        io.startCapture();

        readFileFromInput();

        io.stopCapture();

        string actualOutput = io.getOutput();

        // المقارنة دقيقة جداً: يجب أن تطابق الحروف والسطور كما في البايثون بالضبط
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
