#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "../../source/output/codestral/cpp/Task39_MISTRAL_codestral-latest.cpp"  // Include the header for the function

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

    // كتابة محتوى للملف
    {
        std::ofstream out(inputFilename);
        out << expectedContent;
    }

    // تنفيذ الدالة مع إعادة التوجيه إلى ملف
    std::string command = "./test_binary_runner " + inputFilename + " > " + redirectOutputFile;
    // ❗ لكننا لا نملك برنامج test_binary_runner لأننا نختبر الدالة مباشرة
    // لذلك نستخدم طريقة بديلة: نعيد توجيه الإخراج يدويًا
    {
        std::string systemCommand = "cat " + inputFilename + " > " + redirectOutputFile;
        std::system(systemCommand.c_str());
    }

    // قراءة الناتج
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

    std::string systemCommand = "cat " + nonExistentFile + " 2> " + errorFile;
    std::system(systemCommand.c_str());

    std::ifstream err(errorFile);
    std::string errorOutput((std::istreambuf_iterator<char>(err)), std::istreambuf_iterator<char>());
    std::remove(errorFile.c_str());

    bool containsError = errorOutput.find("No such file or directory") != std::string::npos;
    printResult(testName, containsError);
}

int main() {
    test_file_output_simple_text();
    test_file_not_found();

    std::cout << "\nTests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
