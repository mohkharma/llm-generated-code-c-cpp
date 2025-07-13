#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

#include "../../source/output/gpt4o/cpp/Task70_OPENAI_gpt-4o.cpp"  // Include the header for the function

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
    const string filename = "test_gpt4o.txt";
    const string content = "OpenAI\nGPT-4o\nTest";

    create_test_file(filename, content);

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    printFileContent(filename);

    cout.rdbuf(old_cout);
    remove_test_file(filename);

    bool success = (buffer.str() == "OpenAI\nGPT-4o\nTest\n");
    print_result(test_name, success);
}

void test_file_not_found() {
    const string test_name = "test_file_not_found";
    const string filename = "non_existent_file.txt";

    stringstream buffer;
    streambuf* old_cerr = cerr.rdbuf(buffer.rdbuf());

    printFileContent(filename);

    cerr.rdbuf(old_cerr);

    bool success = buffer.str().find("An error occurred: Could not open the file") != string::npos;
    print_result(test_name, success);
}

int main() {
    test_valid_file();
    test_file_not_found();

    cout << "\nSummary: " << passed << " passed, " << failed << " failed." << endl;
    return failed == 0 ? 0 : 1;
}
