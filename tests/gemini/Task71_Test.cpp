#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/gemini/cpp/Task71_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

using namespace std;

int passed = 0, failed = 0;

void print_result(const string& test_name, bool success) {
    if (success) {
        cout << "[PASS] " << test_name << endl;
        ++passed;
    } else {
        cout << "[FAIL] " << test_name << endl;
        ++failed;
    }
}

void test_valid_integer() {
    const string test_name = "test_valid_integer";
    string input = "123";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    convertToInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "Successfully converted '123' to integer: 123\n";
    print_result(test_name, success);
}

void test_negative_integer() {
    const string test_name = "test_negative_integer";
    string input = "-42";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    convertToInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "Successfully converted '-42' to integer: -42\n";
    print_result(test_name, success);
}

void test_invalid_input() {
    const string test_name = "test_invalid_input";
    string input = "abc";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    convertToInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "Unable to convert 'abc' to an integer.\n";
    print_result(test_name, success);
}

void test_float_input() {
    const string test_name = "test_float_input";
    string input = "12.34";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    convertToInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "Unable to convert '12.34' to an integer.\n";
    print_result(test_name, success);
}

void test_large_number() {
    const string test_name = "test_large_number";
    string input = "999999999999999999999999";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    convertToInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "Unable to convert '999999999999999999999999' to an integer. Value out of range.\n";
    print_result(test_name, success);
}

void test_empty_string() {
    const string test_name = "test_empty_string";
    string input = "";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    convertToInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "Unable to convert '' to an integer.\n";
    print_result(test_name, success);
}

int main() {
    test_valid_integer();
    test_negative_integer();
    test_invalid_input();
    test_float_input();
    test_large_number();
    test_empty_string();

    cout << "\nSummary: " << passed << " passed, " << failed << " failed." << endl;
    return failed == 0 ? 0 : 1;
}
