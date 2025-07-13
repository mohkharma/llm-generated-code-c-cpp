#include "../../../source/output/codestral/cpp/Task131_MISTRAL_codestral-latest.cpp"


#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    string input;
    string expected_output;
    string description;
};

bool run_test(const TestCase& test, int index) {
    try {
        string result = deserialize_data(test.input);
        if (result == test.expected_output) {
            cout << "[PASS] Test " << index + 1 << ": " << test.description << endl;
            return true;
        } else {
            cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
            cout << "Expected: " << test.expected_output << endl;
            cout << "Got     : " << result << endl;
            return false;
        }
    } catch (const exception& e) {
        cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
        cout << "Exception thrown: " << e.what() << endl;
        return false;
    } catch (...) {
        cout << "[FAIL] Test " << index + 1 << ": " << test.description << endl;
        cout << "Unknown exception thrown." << endl;
        return false;
    }
}

int main() {
    vector<TestCase> tests = {
        {
            // this is a serialized string "hello" using boost::archive::binary_oarchive
            "\x1\x0\x0\x0\x8hello",
            "hello",
            "Deserialize 'hello'"
        },
        {
            // this will fail (invalid archive)
            "not a valid archive",
            "",
            "Invalid serialized input"
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
