// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <cassert>

using namespace std;

// Simulate the tested program logic with automated inputs and capture output
string runTest() {
    stringstream input(
        "0\n"
        "9\n"
        "100\n"
        "abc\n"
        "-1\n"
    );
    stringstream output;

    const int bufferSize = 100;
    char* buffer = new char[bufferSize];

    // Initialize buffer with data 'A'...'Z' repeated
    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = 'A' + (i % 26);
    }

    while (true) {
        int index;
        output << "Enter an index to read (0-99), or -1 to exit: ";
        input >> index;

        if (input.fail()) {
            // clear error and read invalid input as string to discard
            input.clear();
            string dummy;
            input >> dummy;
            output << "Error: Invalid input. Please enter a valid integer." << endl;
            continue;
        }

        if (index == -1) {
            break;
        }

        if (index >= 0 && index < bufferSize) {
            output << "Data at index " << index << ": " << buffer[index] << endl;
        } else {
            output << "Invalid index. Please enter a number between 0 and 99." << endl;
        }
    }

    delete[] buffer;
    return output.str();
}

void test() {
    string expected =
        "Enter an index to read (0-99), or -1 to exit: Data at index 0: A\n"
        "Enter an index to read (0-99), or -1 to exit: Data at index 9: J\n"
        "Enter an index to read (0-99), or -1 to exit: Invalid index. Please enter a number between 0 and 99.\n"
        "Enter an index to read (0-99), or -1 to exit: Error: Invalid input. Please enter a valid integer.\n"
        "Enter an index to read (0-99), or -1 to exit: ";

    string actual = runTest();
    assert(actual == expected && "Output does not match expected output.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
