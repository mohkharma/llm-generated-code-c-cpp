#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>

#include "../../../source/output/codestral/cpp/Task125_MISTRAL_codestral-latest.cpp"

int passed = 0, failed = 0;

void assertOutputContains(const std::string& output, const std::string& expected, const std::string& testName) {
    if (output.find(expected) != std::string::npos) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
        std::cout << "  Expected output to contain: \"" << expected << "\"\n";
        std::cout << "  Actual output: \"" << output << "\"\n";
        failed++;
    }
}

void runTestCase(const std::string& input, const std::string& expectedOutput, const std::string& testName) {
    // إعداد ملفات مؤقتة
    std::ofstream inFile("temp_input.txt");
    inFile << input;
    inFile.close();

    FILE* originalStdin = freopen("temp_input.txt", "r", stdin);
    FILE* originalStdout = freopen("temp_output.txt", "w", stdout);

    // استدعاء الدالة المعدلة بدل main
    runResourceAccess();

    // استرجاع stdin و stdout
    freopen("/dev/tty", "r", stdin); // أو "CON" على Windows
    freopen("/dev/tty", "w", stdout);

    std::ifstream outFile("temp_output.txt");
    std::stringstream buffer;
    buffer << outFile.rdbuf();
    std::string output = buffer.str();
    outFile.close();

    std::remove("temp_input.txt");
    std::remove("temp_output.txt");

    assertOutputContains(output, expectedOutput, testName);
}

int main() {
    runTestCase("A\n", "Access granted to: Resource A", "test_input_A");
    runTestCase("B\n", "Access granted to: Resource B", "test_input_B");
    runTestCase("C\n", "Access granted to: Resource C", "test_input_C");
    runTestCase("Z\n", "Access denied. Invalid key.", "test_invalid_input_Z");
    runTestCase("\n", "Access denied. Invalid key.", "test_empty_input");

    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
