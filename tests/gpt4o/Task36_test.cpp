#include "../../source/output/gpt4o/cpp/Task36_OPENAI_gpt-4o.cpp" // عدل المسار حسب مكان الحل

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

class OutputCapture {
    streambuf* oldCout;
    streambuf* oldCerr;
    ostringstream outBuffer;
    ostringstream errBuffer;

public:
    void start() {
        oldCout = cout.rdbuf(outBuffer.rdbuf());
        oldCerr = cerr.rdbuf(errBuffer.rdbuf());
    }
    void stop() {
        cout.rdbuf(oldCout);
        cerr.rdbuf(oldCerr);
    }
    string getStdout() const { return outBuffer.str(); }
    string getStderr() const { return errBuffer.str(); }
    void clear() {
        outBuffer.str("");
        outBuffer.clear();
        errBuffer.str("");
        errBuffer.clear();
    }
};

struct TestCase {
    string filename;
    string fileContent;       // محتوى الملف (فارغ = ملف غير موجود)
    string expectedStdout;
    string expectedStderr;
};

TestCase tests[] = {
    {"test_file.txt", "Hello, World!", "Hello, World!\n", ""},
    {"missing_file.txt", "", "", "Cannot open file: missing_file.txt\n"},
    {"test_file.txt", "", "", "Cannot open file: test_file.txt\n"},
    {"content_file.txt", "File Content", "File Content\n", ""},
    {"empty_file.txt", "", "", "Cannot open file: empty_file.txt\n"},
    {"numeric_file.txt", "12345", "12345\n", ""},
    {"special_chars.txt", "Special Characters !@#$%^&*()", "Special Characters !@#$%^&*()\n", ""},
    {"multiline_file.txt", "Line 1\nLine 2", "Line 1\nLine 2\n", ""}
};

int main() {
    cout << "Running strict tests for readFileFromArgs()...\n";

    OutputCapture cap;
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < total; ++i) {
        const auto& t = tests[i];

        remove(t.filename.c_str());
        if (!t.fileContent.empty()) {
            ofstream f(t.filename);
            f << t.fileContent;
            f.close();
        }

        cap.clear();
        cap.start();

        readFileFromArgs(t.filename.c_str());

        cap.stop();

        string actualOut = cap.getStdout();
        string actualErr = cap.getStderr();

        bool pass = (actualOut == t.expectedStdout) && (actualErr == t.expectedStderr);

        if (pass) {
            cout << "[PASS] Test " << (i+1) << " (" << t.filename << ")\n";
            ++passed;
        } else {
            cout << "[FAIL] Test " << (i+1) << " (" << t.filename << ")\n";
            cout << "  Expected stdout:\n---\n" << t.expectedStdout << "\n---\n";
            cout << "  Actual stdout:\n---\n" << actualOut << "\n---\n";
            cout << "  Expected stderr:\n---\n" << t.expectedStderr << "\n---\n";
            cout << "  Actual stderr:\n---\n" << actualErr << "\n---\n";
        }

        remove(t.filename.c_str());
    }

    cout << "-------------------------\n";
    cout << "Passed " << passed << " out of " << total << " tests.\n";

    return (passed == total) ? 0 : 1;
}
