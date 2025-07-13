#include "../../../source/output/claude/cpp/Task36_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

using namespace std;

// دالة لمساعدتنا بالتقاط إخراج cout و cerr
class OutputCapture {
    std::streambuf* old_cout;
    std::streambuf* old_cerr;
    std::ostringstream out_buffer;
    std::ostringstream err_buffer;

public:
    void start() {
        old_cout = std::cout.rdbuf(out_buffer.rdbuf());
        old_cerr = std::cerr.rdbuf(err_buffer.rdbuf());
    }
    void stop() {
        std::cout.rdbuf(old_cout);
        std::cerr.rdbuf(old_cerr);
    }
    std::string getStdout() const {
        return out_buffer.str();
    }
    std::string getStderr() const {
        return err_buffer.str();
    }
    void clear() {
        out_buffer.str("");
        out_buffer.clear();
        err_buffer.str("");
        err_buffer.clear();
    }
};
struct TestCase {
    string filename;
    string file_content;  // لو فارغ، الملف غير موجود
    string expected_stdout;
    string expected_stderr;
};

int main() {
    cout << "Running Task36 Tests...\n";

    TestCase tests[] = {
        // 1. ملف يحتوي على "Hello, World!"
        {"test_file.txt", "Hello, World!", "Hello, World!\n", ""},

        // 2. ملف غير موجود
        {"missing_file.txt", "", "", "Error: Unable to open file 'missing_file.txt'\n"},

        // 3. محاكاة io error صعبة في هذا الحل، نعاملها كملف غير موجود
        {"io_error.txt", "", "", "Error: Unable to open file 'io_error.txt'\n"},

        // 4. ملف يحتوي على "File Content"
        {"content_file.txt", "File Content", "File Content\n", ""},

        // 5. ملف فارغ
        {"empty_file.txt", "", "", ""},

        // 6. ملف يحتوي على "12345"
        {"numeric_file.txt", "12345", "12345\n", ""},

        // 7. ملف يحتوي على "Special Characters !@#$%^&*()"
        {"special_chars.txt", "Special Characters !@#$%^&*()", "Special Characters !@#$%^&*()\n", ""},

        // 8. ملف متعدد الأسطر "Line 1\nLine 2"
        {"multiline_file.txt", "Line 1\nLine 2", "Line 1\nLine 2\n", ""},

        // 9. ملف يحتوي على "Trailing spaces    "
        {"trailing_spaces.txt", "Trailing spaces    ", "Trailing spaces    \n", ""},

        // 10. ملف يحتوي على "File\nWith\nNewlines"
        {"newlines_file.txt", "File\nWith\nNewlines", "File\nWith\nNewlines\n", ""}
    };

    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    OutputCapture cap;

    for (int i = 0; i < total; ++i) {
        const auto& t = tests[i];

        // حذف الملف أولاً إن كان موجود
        remove(t.filename.c_str());

        if (!t.file_content.empty()) {
            ofstream f(t.filename);
            f << t.file_content;
            f.close();
        }

        cap.clear();
        cap.start();

        readFile(t.filename);

        cap.stop();

        string actual_stdout = cap.getStdout();
        string actual_stderr = cap.getStderr();

        bool pass = (actual_stdout == t.expected_stdout) && (actual_stderr == t.expected_stderr);

        if (pass) {
            cout << "[PASS] Test " << (i+1) << " (" << t.filename << ")\n";
            ++passed;
        } else {
            cout << "[FAIL] Test " << (i+1) << " (" << t.filename << ")\n";
            cout << "  Expected stdout:\n---\n" << t.expected_stdout << "---\n";
            cout << "  Actual stdout:\n---\n" << actual_stdout << "---\n";
            cout << "  Expected stderr:\n---\n" << t.expected_stderr << "---\n";
            cout << "  Actual stderr:\n---\n" << actual_stderr << "---\n";
        }

        remove(t.filename.c_str());
    }

    cout << "-----------------------\n";
    cout << "Passed " << passed << " out of " << total << " tests.\n";

    return (passed == total) ? 0 : 1;
}
