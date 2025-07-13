#include "../../source/output/claude/cpp/Task65_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

void ASSERT_TRUE(bool condition, const std::string& testName, int& passed, int& failed) {
    if (condition) {
        std::cout << "[PASS] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

int main() {
    int passed = 0, failed = 0;

    // test_1_invalid_extension
    {
        std::stringstream buffer;
        std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

        readFile("data.csv");

        std::cout.rdbuf(oldCout);
        std::string output = buffer.str();
        ASSERT_TRUE(output.find("Error: File must have a .txt extension") != std::string::npos, "test_1_invalid_extension", passed, failed);
    }

    // test_2_file_not_exist
    {
        std::stringstream buffer;
        std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

        readFile("nonexistent.txt");

        std::cout.rdbuf(oldCout);
        std::string output = buffer.str();
        ASSERT_TRUE(output.find("Error: File 'nonexistent.txt' does not exist") != std::string::npos, "test_2_file_not_exist", passed, failed);
    }

    // test_3_valid_file_read
    {
        std::string filename = "test_file.txt";
        std::ofstream out(filename);
        out << "Line 1\nLine 2";
        out.close();

        std::stringstream buffer;
        std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

        readFile(filename);

        std::cout.rdbuf(oldCout);
        std::string output = buffer.str();
        bool ok = output.find("File contents:") != std::string::npos &&
                  output.find("Line 1") != std::string::npos &&
                  output.find("Line 2") != std::string::npos;
        ASSERT_TRUE(ok, "test_3_valid_file_read", passed, failed);

        std::filesystem::remove(filename);
    }

    // test_4_no_argument_not_supported
    std::cout << "Note: test_4_no_argument_not_supported not supported by this implementation.\n";
    ASSERT_TRUE(false, "test_4_no_argument_not_supported", passed, failed);

    // summary
    std::cout << "\nTests passed: " << passed << "\nTests failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
