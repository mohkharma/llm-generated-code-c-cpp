#include "../../../source/output/claude/cpp/Task129_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>

void run_test(const std::string& test_name, const std::string& input_filename, const std::string& expected_substring, bool should_exist) {
    std::remove(input_filename.c_str());

    std::stringstream output;
    std::streambuf* orig_cout = std::cout.rdbuf();
    std::streambuf* orig_cerr = std::cerr.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    std::cerr.rdbuf(output.rdbuf());

    // استدعاء الدالة مباشرة
    retrieveFile(input_filename);

    std::cout.rdbuf(orig_cout);
    std::cerr.rdbuf(orig_cerr);

    std::string result = output.str();

    bool contains_message = result.find(expected_substring) != std::string::npos;

    bool file_saved = false;
    std::ifstream check_file(input_filename, std::ios::binary);
    if (check_file.is_open()) {
        file_saved = true;
        check_file.close();
        std::remove(input_filename.c_str());
    }

    bool pass = contains_message && (file_saved == should_exist);

    if (pass) {
        std::cout << "[PASS] " << test_name << std::endl;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "  ⮕ Output: " << result << std::endl;
        std::cout << "  ⮕ Expected: \"" << expected_substring << "\" | File saved? " << (file_saved ? "Yes" : "No") << std::endl;
    }
}

int main() {
    run_test("Retrieve existing file", "testFile.txt", "successfully retrieved and saved", true);
    run_test("Retrieve missing file", "nonexistent.txt", "Error retrieving file", false);
    return 0;
}
