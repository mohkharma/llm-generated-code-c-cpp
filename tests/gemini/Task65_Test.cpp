#include "../../source/output/gemini/cpp/Task65_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

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
    std::cout << "Note: test_1_invalid_extension not supported by this implementation.\n";
    ASSERT_TRUE(false, "test_1_invalid_extension", passed, failed);

    // test_2_file_not_exist
    {
        std::stringstream buffer;
        std::streambuf* oldCerr = std::cerr.rdbuf(buffer.rdbuf());

        std::string result = readFile("nonexistent.txt");

        std::cerr.rdbuf(oldCerr);
        std::string output = buffer.str();
        bool correctError = output.find("Error: Could not open file 'nonexistent.txt'") != std::string::npos;
        ASSERT_TRUE(correctError && result.empty(), "test_2_file_not_exist", passed, failed);
    }

    // test_3_valid_file_read
    {
        std::string filename = "sample.txt";
        std::ofstream out(filename);
        out << "first line\nsecond line";
        out.close();

        std::string result = readFile(filename);
        bool ok = result.find("first line") != std::string::npos &&
                  result.find("second line") != std::string::npos;
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
