// Task190_Test.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

#include "../../../source/output/claude/cpp/Task190_CLAUDE_claude-3-5-sonnet-20240620.cpp"

using namespace std;

struct TestCase {
    string fileContent;
    string expectedOutput;
    string description;
};

bool runTest(const TestCase& test) {
    // كتابة الملف
    ofstream outFile("file.txt");
    outFile << test.fileContent;
    outFile.close();

    // إعادة توجيه cout إلى stringstream
    streambuf* oldCoutBuf = cout.rdbuf();
    stringstream buffer;
    cout.rdbuf(buffer.rdbuf());

    // تشغيل الحل
    solve();

    // استعادة cout
    cout.rdbuf(oldCoutBuf);

    string output = buffer.str();
    string expected = test.expectedOutput;

    // تنظيف النهايات
    if (!output.empty() && output.back() == '\n') output.pop_back();
    if (!expected.empty() && expected.back() == '\n') expected.pop_back();

    if (output == expected) {
        cout << "[✅] Passed: " << test.description << endl;
        return true;
    } else {
        cout << "[❌] Failed: " << test.description << endl;
        cout << "Expected:\n" << expected << endl;
        cout << "Got:\n" << output << endl;
        return false;
    }
}

int main() {
    vector<TestCase> tests = {
        {
            "name age\nalice 21\nryan 30\n",
            "name alice ryan\nage 21 30",
            "Basic transpose"
        },
        {
            "a b c\nd e f\ng h i\n",
            "a d g\nb e h\nc f i",
            "3x3 square matrix"
        },
        {
            "one two\nthree four\n",
            "one three\ntwo four",
            "2x2 test"
        }
    };

    int passed = 0;
    for (const auto& test : tests) {
        if (runTest(test)) passed++;
    }

    cout << "\nSummary: " << passed << "/" << tests.size() << " tests passed." << endl;

    // تنظيف الملف
    remove("file.txt");

    return 0;
}
