#include "../../source/output/gpt4o/cpp/Task45_OPENAI_gpt-4o.cpp"  // Include the header for the function
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>

int testsPassed = 0;
int testsFailed = 0;

void printResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "[PASS] " << testName << "\n";
        ++testsPassed;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        ++testsFailed;
    }
}

std::string runWithInput(const std::string& inputStr) {
    // اكتب الإدخال في ملف مؤقت
    FILE* inputFile = tmpfile();
    fwrite(inputStr.c_str(), 1, inputStr.size(), inputFile);
    rewind(inputFile);

    // أنشئ ملف مؤقت للإخراج
    FILE* outputFile = tmpfile();

    // احفظ stdin و stdout الأصلية
    FILE* originalStdin = stdin;
    FILE* originalStdout = stdout;

    // وجّه stdin و stdout
    freopen("/dev/null", "r", stdin);  // workaround لـ CLion
    freopen("/dev/null", "w", stdout); // ""

    stdin = inputFile;
    stdout = outputFile;

    // استدعِ الدالة
    readIntegerC();

    // ارجع stdin و stdout كما كانت
    fflush(stdout);
    stdin = originalStdin;
    stdout = originalStdout;

    // اقرأ الإخراج
    fseek(outputFile, 0, SEEK_SET);
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return std::string(buffer);
}

int main() {
    // Test 1: valid integer
    {
        std::string output = runWithInput("42\n");
        bool pass = output.find("C read the number: 42") != std::string::npos;
        printResult("test_valid_integer", pass);
    }

    // Test 2: invalid input
    {
        std::string output = runWithInput("abc\n");
        bool pass = output.find("Invalid input in C") != std::string::npos;
        printResult("test_invalid_input", pass);
    }

    // Test 3: negative number
    {
        std::string output = runWithInput("-17\n");
        bool pass = output.find("C read the number: -17") != std::string::npos;
        printResult("test_negative_input", pass);
    }

    // Test 4: zero
    {
        std::string output = runWithInput("0\n");
        bool pass = output.find("C read the number: 0") != std::string::npos;
        printResult("test_zero_input", pass);
    }

    std::cout << "\nTests passed: " << testsPassed << "\n";
    std::cout << "Tests failed: " << testsFailed << "\n";

    return testsFailed == 0 ? 0 : 1;
}
