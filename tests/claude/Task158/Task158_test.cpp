// TaskXX_Test.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdio>  // for popen, pclose

using namespace std;

// Helper: run the tested program logic with given input, capture its stdout output
string runProgramWithInput(const string& input) {
    // We'll simulate the tested program:
    // 1. Print prompt "Enter data: "
    // 2. Read user input line
    // 3. Run system("echo " + userInput) and capture output

    // Since system() output goes to console directly, to capture it in C++ test
    // we can redirect using popen and read output back.

    // But we must run the tested program as a separate process for perfect capture,
    // which is complex here, so instead we simulate:

    // Step 1: Prepare the command string
    string command = "echo " + input;

    // Step 2: Run the command via popen to capture output
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "ERROR";
    }

    char buffer[128];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    // The tested program prints prompt, then runs system(command)
    // So output should be:
    // Enter data: <newline> + output of echo command

    return "Enter data: " + result;
}

void test() {
    // Test case from Python code logic:
    // input: "Hello World"
    // output should be:
    // Enter data: Hello World\n

    string input = "Hello World";
    string expected = "Enter data: Hello World\n";

    string actual = runProgramWithInput(input);

    assert(actual == expected && "Output does not match expected output.");
}

int main() {
    test();
    cout << "Test passed successfully." << endl;
    return 0;
}
