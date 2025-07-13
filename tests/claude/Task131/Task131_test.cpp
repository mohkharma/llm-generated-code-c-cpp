#define main dont_run_main
#include "../../../source/output/claude/cpp/Task131_CLAUDE_claude-3-5-sonnet-20240620.cpp"
#undef main

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    string input;
    string expected_output;
    string description;
};

bool run_test(const TestCase& test, int index) {
    // Redirect cin and cout using stringstream
    stringstream input_stream(test.input);
    stringstream output_stream;

    // Backup original buffers
    streambuf* cin_backup = cin.rdbuf();
    streambuf* cout_backup = cout.rdbuf();

    // Redirect
    cin.rdbuf(input_stream.rdbuf());
    cout.rdbuf(output_stream.rdbuf());

    // Run the solution's logic (which was originally in main)
    dont_run_main();

    // Restore original buffers
    cin.rdbuf(cin_backup);
    cout.rdbuf(cout_backup);

    // Capture and compare output
    string actual_output = output_stream.str();

    auto trim = [](const string& str) {
        size_t first = str.find_first_not_of(" \n\r\t");
        size_t last = str.find_last_not_of(" \n\r\t");
        if (first == string::npos || last == string::npos) return string();
        return str.substr(first, last - first + 1);
    };

    if (trim(actual_output) == trim(test.expected_output)) {
        cout << "[PASS] Test " << index + 1 << ": " << test.description << endl;
        return true;
    } else {
        cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
        cout << "Expected:\n" << test.expected_output << endl;
        cout << "Got:\n" << actual_output << endl;
        return false;
    }
}

int main() {
    vector<TestCase> tests = {
        {
            R"({"name": "Alice", "age": 25})",
            "Enter serialized data (JSON format): Deserialized data:\n{\n  \"age\": 25,\n  \"name\": \"Alice\"\n}",
            "Valid JSON object"
        },
        {
            R"(["apple", "banana", "cherry"])",
            "Enter serialized data (JSON format): Deserialized data:\n[\n  \"apple\",\n  \"banana\",\n  \"cherry\"\n]",
            "Valid JSON array"
        },
        {
            R"(invalid json)",
            "Enter serialized data (JSON format): Error: Invalid JSON data",
            "Invalid JSON input"
        }
    };

    int passed = 0;
    for (size_t i = 0; i < tests.size(); ++i) {
        if (run_test(tests[i], i)) {
            ++passed;
        }
    }

    cout << "------------------------" << endl;
    cout << "Passed " << passed << " out of " << tests.size() << " tests." << endl;

    return 0;
}
