#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <string>

#include "../../source/output/claude/cpp/Task70_CLAUDE_claude-3-5-sonnet-20240620.cpp"  // Include the header for the function

using namespace std;

int passed = 0, failed = 0;

void print_result(const string& test_name, bool success) {
    if (success) {
        cout << "[PASS] " << test_name << endl;
        ++passed;
    } else {
        cout << "[FAIL] " << test_name << endl;
        ++failed;
    }
}

// Helper: create a file with content
void create_test_file(const string& filename, const string& content) {
    ofstream file(filename);
    file << content;
    file.close();
}

// Helper: remove a file
void remove_test_file(const string& filename) {
    std::filesystem::remove(filename);
}

void test_valid_file() {
    const string test_name = "test_valid_file";
    const string filename = "test_valid.txt";
    const string content = "Hello\nWorld\n123";

    create_test_file(filename, content);

    // Redirect stdout
    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    readFile(filename);

    cout.rdbuf(old_cout);
    remove_test_file(filename);

    bool success = buffer.str() == "Hello\nWorld\n123\n";
    print_result(test_name, success);
}

void test_file_not_found() {
    const string test_name = "test_file_not_found";
    const string filename = "non_existent.txt";

    // Redirect stderr
    stringstream buffer;
    streambuf* old_cerr = cerr.rdbuf(buffer.rdbuf());

    readFile(filename);

    cerr.rdbuf(old_cerr);

    bool success = buffer.str().find("Unable to open file") != string::npos;
    print_result(test_name, success);
}

int main() {
    test_valid_file();
    test_file_not_found();

    cout << "\nSummary: " << passed << " passed, " << failed << " failed." << endl;
    return failed == 0 ? 0 : 1;
}
