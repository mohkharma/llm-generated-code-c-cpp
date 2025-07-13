#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>


#include "../../../source/output/gemini/cpp/Task125_GEMINI_gemini-1.5-pro-001.cpp"

int passed = 0, failed = 0;

void assertOutputContains(const std::string& output, const std::vector<std::string>& expectedLines, const std::string& testName) {
    bool allFound = true;
    for (const std::string& expected : expectedLines) {
        if (output.find(expected) == std::string::npos) {
            allFound = false;
            std::cout << "[FAILED] " << testName << "\n";
            std::cout << "  Missing expected output: \"" << expected << "\"\n";
        }
    }

    if (allFound) {
        std::cout << "[PASSED] " << testName << "\n";
        passed++;
    } else {
        failed++;
    }
}

std::string runTestInput(const std::string& input) {
    std::ofstream inFile("temp_input.txt");
    inFile << input;
    inFile.close();

    FILE* originalStdin = freopen("temp_input.txt", "r", stdin);
    FILE* originalStdout = freopen("temp_output.txt", "w", stdout);

    runRoleAccess();

    // Restore stdin and stdout
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);

    std::ifstream outFile("temp_output.txt");
    std::stringstream buffer;
    buffer << outFile.rdbuf();
    std::string output = buffer.str();
    outFile.close();

    std::remove("temp_input.txt");
    std::remove("temp_output.txt");

    return output;
}

int main() {
    std::string out;

    out = runTestInput("admin\n");
    assertOutputContains(out, {
        "Available resources for admin:",
        "resource1", "resource2", "resource3"
    }, "test_admin");

    out = runTestInput("editor\n");
    assertOutputContains(out, {
        "Available resources for editor:",
        "resource2", "resource3"
    }, "test_editor");

    out = runTestInput("viewer\n");
    assertOutputContains(out, {
        "Available resources for viewer:",
        "resource3"
    }, "test_viewer");

    out = runTestInput("guest\n");
    assertOutputContains(out, {
        "Invalid role."
    }, "test_invalid_role");

    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";

    if (failed == 0) {
        std::cout << "\n✅ All tests passed successfully. ✅\n";
    }

    return failed == 0 ? 0 : 1;
}
