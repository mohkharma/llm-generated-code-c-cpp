#include "../../../source/output/llama-3/cpp/Task131_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    string input;
    vector<string> expected_lines;
    string description;
};

bool run_test(const TestCase& test, int index) {
    stringstream output_capture;
    streambuf* cout_backup = cout.rdbuf();
    cout.rdbuf(output_capture.rdbuf());

    // استدعاء الدالة
    DeserializeData::deserializeData(test.input);

    cout.rdbuf(cout_backup);

    // تحليل الناتج إلى أسطر
    vector<string> actual_lines;
    string line;
    stringstream ss(output_capture.str());
    while (getline(ss, line)) {
        actual_lines.push_back(line);
    }

    // تحقق عدد الأسطر
    if (actual_lines.size() != test.expected_lines.size()) {
        cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
        cout << "Expected lines: " << test.expected_lines.size() << ", Got: " << actual_lines.size() << endl;
        return false;
    }

    // تحقق كل سطر
    for (size_t i = 0; i < actual_lines.size(); ++i) {
        if (actual_lines[i] != test.expected_lines[i]) {
            cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
            cout << "Mismatch at line " << (i+1) << endl;
            cout << "Expected: \"" << test.expected_lines[i] << "\"\n";
            cout << "Got     : \"" << actual_lines[i] << "\"\n";
            return false;
        }
    }

    cout << "[PASS] Test " << index + 1 << ": " << test.description << endl;
    return true;
}

int main() {
    vector<TestCase> tests = {
        {
            "key1:value1:key2:value2:key3:value3:",
            {
                "Deserialized data: value1 = key2",
                "Deserialized data: value3 = "
            },
            "Test with 3 key:value pairs"
        },
        {
            "a:b:c:d:",
            {
                "Deserialized data: b = c",
            },
            "Test with 2 key:value pairs"
        },
        {
            "",
            {},
            "Empty input"
        }
    };

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        if (run_test(tests[i], i))
            ++passed;
    }

    cout << "------------------------" << endl;
    cout << "Passed " << passed << " out of " << tests.size() << " tests." << endl;

    return 0;
}
