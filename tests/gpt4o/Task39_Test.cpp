#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "../../source/output/gpt4o/cpp/Task39_OPENAI_gpt-4o.cpp"  // Include the header for the function
int passed = 0;
int failed = 0;

void printResult(const std::string& testName, bool success) {
    if (success) {
        std::cout << "[PASS] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

void test_file_output_simple_text() {
    std::string testName = "test_file_output_simple_text";
    std::string inputFilename = "testfile1.txt";
    std::string redirectOutputFile = "output.txt";
    std::string expectedContent = "Hello, world!\n";

    // إنشاء ملف اختبار
    {
        std::ofstream out(inputFilename);
        out << expectedContent;
    }

    // إعادة التوجيه حسب النظام
#ifdef _WIN32
    std::string command = "type " + inputFilename + " > " + redirectOutputFile;
#else
    std::string command = "cat " + inputFilename + " > " + redirectOutputFile;
#endif

    std::system(command.c_str());

    // قراءة النتيجة من ملف الإخراج
    std::ifstream in(redirectOutputFile);
    std::string actualOutput((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    // تنظيف الملفات
    std::remove(inputFilename.c_str());
    std::remove(redirectOutputFile.c_str());

    printResult(testName, actualOutput == expectedContent);
}

void test_file_not_found() {
    std::string testName = "test_file_not_found";
    std::string nonExistentFile = "non_existent_file.txt";
    std::string errorFile = "error_output.txt";

    // إعادة توجيه stderr
#ifdef _WIN32
    std::string command = "type " + nonExistentFile + " 2> " + errorFile;
#else
    std::string command = "cat " + nonExistentFile + " 2> " + errorFile;
#endif

    std::system(command.c_str());

    std::ifstream err(errorFile);
    std::string errorOutput((std::istreambuf_iterator<char>(err)), std::istreambuf_iterator<char>());
    std::remove(errorFile.c_str());

#ifdef _WIN32
    bool containsError = errorOutput.find("The system cannot find the file") != std::string::npos;
#else
    bool containsError = errorOutput.find("No such file or directory") != std::string::npos;
#endif

    printResult(testName, containsError);
}

int main() {
    test_file_output_simple_text();
    test_file_not_found();

    std::cout << "\nTests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
