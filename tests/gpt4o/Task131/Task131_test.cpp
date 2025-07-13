#include "../../../source/output/gpt4o/cpp/Task131_OPENAI_gpt-4o.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>  // for remove()
#include <sstream>

using namespace std;

struct TestCase {
    string file_content;
    string expected_output;
    string description;
};

bool run_test(const TestCase& test, int index) {
    string temp_filename = "temp_input_file.txt";

    // Write the test content to a temporary file
    {
        ofstream temp_out(temp_filename);
        temp_out << test.file_content;
    }

    // Prepare output stream
    stringstream output;

    // Test reading and writing
    try {
        ifstream input(temp_filename);
        if (!input) {
            cerr << "[FAIL] Test " << index + 1 << ": " << test.description << " (Could not open file)" << endl;
            return false;
        }

        UserData user;
        input >> user;

        output << user;
        input.close();
    } catch (const exception& e) {
        cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
        cout << "Exception thrown: " << e.what() << endl;
        remove(temp_filename.c_str());
        return false;
    }

    // Clean up
    remove(temp_filename.c_str());

    string actual_output = output.str();

    if (actual_output == test.expected_output) {
        cout << "[PASS] Test " << index + 1 << ": " << test.description << endl;
        return true;
    } else {
        cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
        cout << "Expected: \"" << test.expected_output << "\"\n";
        cout << "Got     : \"" << actual_output << "\"\n";
        return false;
    }
}

int main() {
    vector<TestCase> tests = {
        {
            "hello_world",
            "hello_world",
            "Single word from file"
        },
        {
            "multiple words here",
            "multiple",
            "Only first word is extracted"
        },
        {
            "",
            "",
            "Empty file"
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
