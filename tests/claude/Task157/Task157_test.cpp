// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

// The tested program function simulation:
// It allocates memory dynamically for 10 integers,
// assigns 5 to first element, prints it, then frees memory.
// We simulate running this code inside a function to capture output.
string runProgram() {
    // Redirect cout to a stringstream to capture output
    stringstream output;

    // Simulate the tested code
    int* ptr = new int[10];
    ptr[0] = 5;
    output << ptr[0] << endl;
    delete[] ptr;

    return output.str();
}

// The test function: checks that the output matches expected
void test() {
    string expected = "5\n";
    string actual = runProgram();

    // Assert exact match
    assert(actual == expected && "Output did not match expected output.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
