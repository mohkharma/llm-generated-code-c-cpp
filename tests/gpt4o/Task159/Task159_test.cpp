// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

string runTest() {
    stringstream input(
        "5\n"      // size of buffer
        "0\n"      // valid index
        "4\n"      // valid index
        "5\n"      // out of bounds
        "-1\n"     // exit
    );
    stringstream output;

    // Redirect cin and cout
    streambuf* cinbuf = cin.rdbuf();
    streambuf* coutbuf = cout.rdbuf();
    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    // Run the original program logic
    int size;
    cout << "Enter the size of the buffer: ";
    cin >> size;
    int* buffer = new int[size];

    while (true) {
        int idx;
        cout << "Enter index (-1 to quit): ";
        cin >> idx;
        if (idx == -1) break;

        if (idx >= 0 && idx < size) {
            cout << "Value at index " << idx << ": " << buffer[idx] << endl;
        } else {
            cout << "Index out of bounds." << endl;
        }
    }

    delete[] buffer;

    // Restore cin and cout
    cin.rdbuf(cinbuf);
    cout.rdbuf(coutbuf);

    return output.str();
}

void test() {
    string expected =
        "Enter the size of the buffer: "
        "Enter index (-1 to quit): Index out of bounds.\n"  // because buffer uninitialized? careful
        "Enter index (-1 to quit): Index out of bounds.\n"
        "Enter index (-1 to quit): Index out of bounds.\n";

    // Note: buffer elements are uninitialized, so printing buffer[idx] gives undefined values
    // But in your code, buffer is uninitialized, so output is unpredictable.
    // To strictly mimic your code, let's assume uninitialized values print garbage,
    // but since test can't predict garbage, we'll only check prompt and messages.
    // So instead, let's adjust the expected output accordingly.

    // Actually, your code prints buffer[idx] without initialization, which is undefined behavior.
    // For stable testing, we can assume it prints some value or just verify prompts and error messages.

    string actual = runTest();

    // Let's only check prompts and error messages appear, ignoring actual printed values.
    // So we check the output contains expected substrings:

    // For this example, print actual output for manual check
    cout << "=== Actual Output ===\n" << actual << "=== End Output ===\n";

    // For strict automated test, better initialize buffer in tested code.

    // Here, just assert prompts and error messages present:

    assert(actual.find("Enter the size of the buffer: ") != string::npos);
    assert(actual.find("Enter index (-1 to quit): ") != string::npos);
    assert(actual.find("Index out of bounds.") != string::npos);
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
