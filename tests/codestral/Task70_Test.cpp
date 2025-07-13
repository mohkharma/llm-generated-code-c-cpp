#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "../../source/output/codestral/cpp/Task70_MISTRAL_codestral-latest.cpp"  // Include the header for the function

using namespace std;

int passed = 0, failed = 0;

void print_result(const string& test_name, bool success) {
    if (success) {
        cout << "[PASS] " << test_name << endl;
        passed++;
    } else {
        cout << "[FAIL] " << test_name << endl;
        failed++;
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
    const string filename = "test_file.txt";
    const string content = "Hello, file!\nSecond line.";

    create_test_file(filename, content);

    string result = readFile(filename);
    remove_test_file(filename);

    bool success = (result == content);
    print_result(test_name, success);
}

void test_file_not_found() {
    const string test_name = "test_file_not_found";
    const string filename = "does_not_exist.txt";

    string result = readFile(filename);
    bool success = (result == "File not found.");
    print_result(test_name, success);
}

int main() {
    test_valid_file();
    test_file_not_found();

    cout << "\nSummary: " << passed << " passed, " << failed << " failed." << endl;
    return failed == 0 ? 0 : 1;
}
