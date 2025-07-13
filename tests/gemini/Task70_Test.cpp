#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

#include "../../source/output/gemini/cpp/Task70_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

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

void create_test_file(const string& filename, const string& content) {
    ofstream file(filename);
    file << content;
    file.close();
}

void remove_test_file(const string& filename) {
    std::filesystem::remove(filename);
}

void test_valid_file() {
    const string test_name = "test_valid_file";
    const string filename = "temp_test_file.txt";
    const string content = "Line1\nLine2\nLine3";

    create_test_file(filename, content);

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    readFileLines(filename);

    cout.rdbuf(old_cout);
    remove_test_file(filename);

    bool success = buffer.str() == "Line1\nLine2\nLine3\n";
    print_result(test_name, success);
}

void test_file_not_found() {
    const string test_name = "test_file_not_found";
    const string filename = "non_existing_file.txt";

    stringstream buffer;
    streambuf* old_cerr = cerr.rdbuf(buffer.rdbuf());

    readFileLines(filename);

    cerr.rdbuf(old_cerr);

    bool success = buffer.str().find("Error: Unable to open file") != string::npos;
    print_result(test_name, success);
}

int main() {
    test_valid_file();
    test_file_not_found();

    cout << "\nSummary: " << passed << " passed, " << failed << " failed." << endl;
    return failed == 0 ? 0 : 1;
}
