 #include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

string runProgram() {
    stringstream output;

    int* int_ptr = new int(10);
    output << "Value at allocated memory: " << *int_ptr << "\n";

    delete int_ptr;
    return output.str();
}

void test() {
    string expected = "Value at allocated memory: 10\n";
    string actual = runProgram();

    assert(actual == expected && "Output does not match expected output.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
