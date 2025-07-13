// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

string runTest() {
    // Prepare buffer.dat file with 1024 zeros
    {
        ofstream outfile("buffer.dat", ios::binary);
        char zero = 0;
        for (int i = 0; i < 1024; i++) {
            outfile.write(&zero, sizeof(zero));
        }
    }

    // Prepare input with indices: 0, 1023, 1024 (out of range), then exit
    stringstream input("0\n1023\n1024\n");
    stringstream output;

    for (int i = 0; i < 3; i++) {
        output << "Enter index: ";
        int index;
        input >> index;

        if (!input) break;

        ifstream infile("buffer.dat", ios::binary);
        // If index is out of file range, reading will fail
        infile.seekg(index);
        char value = -1;  // default invalid value
        infile.read(&value, sizeof(value));
        infile.close();

        if (index < 0 || index >= 1024) {
            output << "Invalid index." << endl;
        } else {
            output << "Value at index: " << static_cast<int>(value) << endl;
        }
    }

    return output.str();
}

void test() {
    string expected =
        "Enter index: Value at index: 0\n"
        "Enter index: Value at index: 0\n"
        "Enter index: Invalid index.\n";

    string actual = runTest();
    assert(actual == expected && "Output did not match expected.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
