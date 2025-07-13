#define main dont_run_main
#include "../../../source/output/gemini/cpp/Task131_GEMINI_gemini-1.5-pro-001.cpp"
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
    stringstream input_stream(test.input);
    stringstream output_stream;

    streambuf* cin_backup = cin.rdbuf();
    streambuf* cout_backup = cout.rdbuf();
    streambuf* cerr_backup = cerr.rdbuf();

    cin.rdbuf(input_stream.rdbuf());
    cout.rdbuf(output_stream.rdbuf());
    cerr.rdbuf(output_stream.rdbuf());  // redirect errors too

    // Run the solution
    dont_run_main();

    cin.rdbuf(cin_backup);
    cout.rdbuf(cout_backup);
    cerr.rdbuf(cerr_backup);

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
            R"({"name": "Abood", "age": 30})",
            "Enter the data to deserialize: {\n  \"age\": 30,\n  \"name\": \"Abood\"\n}",
            "Valid JSON object"
        },
        {
            R"(["x", "y", "z"])",
            "Enter the data to deserialize: [\n  \"x\",\n  \"y\",\n  \"z\"\n]",
            "Valid JSON array"
        },
        {
            R"(this is not json)",
            "Enter the data to deserialize: Error deserializing data:",
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
