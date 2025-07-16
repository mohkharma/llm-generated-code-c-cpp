#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string userInput;
    int integerValue;

    cout << "Enter an integer: ";
    getline(cin, userInput);

    stringstream ss(userInput);
    if (ss >> integerValue) {
        cout << "Successfully converted to integer: " << integerValue << endl;
        cout << "Test case result: PASS" << endl;
    } else {
        cout << "Invalid input. Please enter a valid integer." << endl;
        cout << "Test case result: FAIL" << endl;
    }

    return 0;
}
