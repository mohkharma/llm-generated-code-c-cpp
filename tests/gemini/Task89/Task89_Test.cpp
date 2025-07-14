#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool checkPassword(const string& storedPassword) {
    string enteredPassword;
    cout << "Enter password: ";
    cin >> enteredPassword;
    if (enteredPassword.length() != storedPassword.length()) {
        return false;
    }
    for (size_t i = 0; i < storedPassword.length(); ++i) {
        if (storedPassword[i] != enteredPassword[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/gemini/Task89/password.txt");
    if (!file.is_open()) {
        cerr << "Password file not found. Please create 'password.txt'." << endl;
        cout << "Test case 1 result: FAIL" << endl;
        return 1;
    }

    string storedPassword;
    getline(file, storedPassword);
    file.close();

    if (checkPassword(storedPassword)) {
        cout << "Passwords match." << endl;
        cout << "Test case 1 result: PASS" << endl;
    } else {
        cout << "Passwords do not match." << endl;
        cout << "Test case 1 result: FAIL" << endl;
    }

    return 0;
}
