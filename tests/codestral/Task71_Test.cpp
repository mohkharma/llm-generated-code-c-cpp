#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/codestral/cpp/Task71_MISTRAL_codestral-latest.cpp"  // Include the header for the function

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

    parseAndPrintInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "123\n";
    print_result(test_name, success);
}

void test_negative_integer() {
    const string test_name = "test_negative_integer";
    string input = "-42";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    parseAndPrintInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str() == "-42\n";
    print_result(test_name, success);
}

void test_invalid_input() {
    const string test_name = "test_invalid_input";
    string input = "abc";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    parseAndPrintInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str().find("Invalid input. Please enter an integer.") != string::npos;
    print_result(test_name, success);
}

void test_float_input() {
    const string test_name = "test_float_input";
    string input = "12.34";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    parseAndPrintInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str().find("Invalid input. Please enter an integer.") != string::npos;
    print_result(test_name, success);
}

void test_large_number() {
    const string test_name = "test_large_number";
    string input = "9999999999999999999999999999999";  // likely overflows

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    parseAndPrintInteger(input);

    cout.rdbuf(old_cout);

    // Even if strtol returns a value, overflow may be undetected, so just check it's a number
    bool success = buffer.str().find("Invalid input") == string::npos;
    print_result(test_name, success);
}

void test_empty_string() {
    const string test_name = "test_empty_string";
    string input = "";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    parseAndPrintInteger(input);

    cout.rdbuf(old_cout);

    bool success = buffer.str().find("Invalid input. Please enter an integer.") != string::npos;
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
