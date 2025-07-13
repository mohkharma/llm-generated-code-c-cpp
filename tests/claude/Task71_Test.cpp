#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/claude/cpp/Task71_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

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
    int result = convertToInt(input);

    bool success = result == 123;
    print_result(test_name, success);
}

void test_negative_integer() {
    const string test_name = "test_negative_integer";
    string input = "-42";
    int result = convertToInt(input);

    bool success = result == -42;
    print_result(test_name, success);
}

void test_invalid_input() {
    const string test_name = "test_invalid_input";
    string input = "abc";
    int result = convertToInt(input);

    bool success = result == -1;
    print_result(test_name, success);
}

void test_float_input() {
    const string test_name = "test_float_input";
    string input = "12.34";
    int result = convertToInt(input);

    bool success = result == -1;
    print_result(test_name, success);
}

void test_large_number() {
    const string test_name = "test_large_number";
    string input = "99999999999999999999999999";  // likely out of range
    int result = convertToInt(input);

    bool success = result == -1;
    print_result(test_name, success);
}

void test_empty_string() {
    const string test_name = "test_empty_string";
    string input = "";
    int result = convertToInt(input);

    bool success = result == -1;
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
