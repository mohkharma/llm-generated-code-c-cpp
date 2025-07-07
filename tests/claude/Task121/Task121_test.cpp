#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

// ✅ استخدم مسار الحل الصحيح الخاص بك هنا
#include "../../../source/output/claude/cpp/Task121_CLAUDE_claude-3-5-sonnet-20240620.cpp"

namespace fs = std::filesystem;

std::string getExpectedOutput(const std::string& filename) {
    std::ostringstream expected;
    expected << "Enter the filename to upload: ";  // ✅ حتى يتطابق مع إخراج uploadFile()

    std::string path = "testFiles/" + filename;

    if (!fs::exists(path)) {
        expected << "File '" << filename << "' not found.\n";
    } else {
        std::ifstream file(path, std::ios::binary);
        std::vector<char> content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        expected << "File '" << filename << "' uploaded successfully.\n";
        expected << "File size: " << content.size() << " bytes\n";
    }

    return expected.str();
}

int main() {
    std::vector<std::string> filenames = {
        "test_file_1.txt",
        "large_file.txt",
        "file_with_!@#$%^&*()_+[]{};,.txt",
        "file_no_extension",
        "empty_file.txt",
        "non_existent_file.txt",
        "file with spaces.txt",
        "a_very_long_filename_that_exceeds_normal_length_limits_for_filenames.txt",
        "image_file.png",
        "file_with_newlines.txt",
        "file_not_found.txt"
    };

    int passed = 0;
    int total = filenames.size();

    for (const std::string& filename : filenames) {
        // محاكاة الإدخال
        std::istringstream input(filename + "\n");
        std::streambuf* origCin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        // التقاط الإخراج
        std::ostringstream output;
        std::streambuf* origCout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        // تشغيل الدالة من الحل
        uploadFile();

        // إعادة التوجيه إلى الأصل
        std::cin.rdbuf(origCin);
        std::cout.rdbuf(origCout);

        // مقارنة الإخراج
        std::string actual = output.str();
        std::string expected = getExpectedOutput(filename);

        if (actual == expected) {
            std::cout << "[✅] Passed: " << filename << "\n";
            passed++;
        } else {
            std::cout << "[❌] Failed: " << filename << "\n";
            std::cout << "Expected:\n" << expected;
            std::cout << "Got:\n" << actual;
        }

        std::cout << "------------------------\n";
    }

    std::cout << "Summary: " << passed << "/" << total << " tests passed.\n";
    return 0;
}
