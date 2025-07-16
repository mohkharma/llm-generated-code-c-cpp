#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

int main() {
    ifstream file("/home/kali/CLionProjects/llm-generated-code-cpp/tests/gemini/Task99/inputs.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        cout << "Test case result: FAIL" << endl;
        return 1;
    }

    string line;
    regex pattern("^\\d+\\.$");
    bool matched = false;

    while (getline(file, line)) {
        // Trim whitespace as in Python's strip()
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (regex_match(line, pattern)) {
            cout << line << endl;
            matched = true;
        }
    }

    file.close();

    if (matched) {
        cout << "Test case result: PASS" << endl;
    } else {
        cout << "Test case result: FAIL" << endl;
    }

    return 0;
}
