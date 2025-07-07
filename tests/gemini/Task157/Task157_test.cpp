 #include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

 string runProgram() {
    stringstream output;

    int* ptr = new int;
    *ptr = 10;
    output << *ptr << "\n";
    delete ptr;

    return output.str();
}

void test() {
    string expected = "10\n";
    string actual = runProgram();
    assert(actual == expected && "Output does not match expected output.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
