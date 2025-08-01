#include <iostream>
#include <limits>

using namespace std;

int getIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
