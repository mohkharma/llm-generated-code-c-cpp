#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

#include "../../source/output/llama-3/cpp/Task70_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"  // Include the header for the function

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
    const string filename = "test_llama.txt";
    const string content = "This is LLaMA\nReading test\nEnd";

    create_test_file(filename, content);

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    readFileAndPrint(filename);

    cout.rdbuf(old_cout);
    remove_test_file(filename);

    bool success = buffer.str() == "This is LLaMA\nReading test\nEnd\n";
    print_result(test_name, success);
}

void test_file_not_found() {
    const string test_name = "test_file_not_found";
    const string filename = "no_such_file.txt";

    stringstream buffer;
    streambuf* old_cout = cout.rdbuf(buffer.rdbuf());

    readFileAndPrint(filename);

    cout.rdbuf(old_cout);

    bool success = buffer.str().find("File not found") != string::npos;
    print_result(test_name, success);
}

int main() {
    test_valid_file();
    test_file_not_found();

    cout << "\nSummary: " << passed << " passed, " << failed << " failed." << endl;
    return failed == 0 ? 0 : 1;
}
