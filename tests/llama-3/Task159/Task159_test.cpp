// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

string runTest() {
    // Simulated user input:
    // 5 (buffer size)
    // 0, 4, 5 (invalid), -1 (exit)
    stringstream input(
        "5\n"
        "0\n"
        "4\n"
        "5\n"
        "-1\n"
    );
    stringstream output;

    // Redirect cin and cout
    streambuf* cinbuf = cin.rdbuf();
    streambuf* coutbuf = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    // Program logic (same as original)
    int bufferSize;
    cout << "Enter the buffer size: ";
    cin >> bufferSize;

    int* buffer = new int[bufferSize];
    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = i;
    }

    while (true) {
        int index;
        cout << "Enter the index to read from the buffer (or -1 to exit): ";
        cin >> index;
        if (index == -1) {
            break;
        }
        if (index < 0 || index >= bufferSize) {
            cout << "Invalid index" << endl;
        } else {
            cout << "Buffer[" << index << "] = " << buffer[index] << endl;
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
        "Enter the buffer size: "
        "Enter the index to read from the buffer (or -1 to exit): Buffer[0] = 0\n"
        "Enter the index to read from the buffer (or -1 to exit): Buffer[4] = 4\n"
        "Enter the index to read from the buffer (or -1 to exit): Invalid index\n"
        "Enter the index to read from the buffer (or -1 to exit): ";

    string actual = runTest();

    assert(actual == expected && "Output does not match expected.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
