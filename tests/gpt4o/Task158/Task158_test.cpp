#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdio>

using namespace std;

// محاكاة الإخراج المتوقع بناءً على الإدخال
string simulateProgramOutput(const string& inputCommand) {
    string prompt = "Enter the command to execute: ";

    // ننفذ الأمر عبر popen لالتقاط الإخراج
    FILE* pipe = popen(inputCommand.c_str(), "r");
    if (!pipe) return "ERROR\n";

    char buffer[128];
    string output;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    pclose(pipe);

    return prompt + output;
}

void test() {
    string input = "echo Test123";
    string expected = "Enter the command to execute: Test123\n";

    string actual = simulateProgramOutput(input);

    assert(actual == expected && "Output does not match expected.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
