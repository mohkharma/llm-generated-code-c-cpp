#include "../../../source/output/gpt4o/cpp/Task127_OPENAI_gpt-4o.cpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

int main() {
    int passed = 0;
    int total = 2;

    std::string sourceFile = "source_sample.txt";
    std::string destFile = "destination_sample.txt";

    // ✅ Test 1: Successful file copy
    try {
        std::ofstream src(sourceFile);
        src << "C++ test content\nLine two.";
        src.close();

        copy_file(sourceFile, destFile);

        std::ifstream s1(sourceFile), s2(destFile);
        std::stringstream buf1, buf2;
        buf1 << s1.rdbuf();
        buf2 << s2.rdbuf();

        if (buf1.str() == buf2.str()) {
            std::cout << "[PASS] Test 1: File copied successfully and contents match\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 1: File contents do not match\n";
        }
    } catch (const std::exception& e) {
        std::cout << "[FAIL] Test 1: Exception occurred - " << e.what() << "\n";
    }

    // ✅ Test 2: Source file does not exist
    try {
        if (fs::exists(sourceFile)) fs::remove(sourceFile);
        if (fs::exists(destFile)) fs::remove(destFile);

        copy_file(sourceFile, destFile);

        std::cout << "[FAIL] Test 2: Expected exception for missing source file\n";
    } catch (const std::exception& e) {
        std::cout << "[PASS] Test 2: Correctly threw exception - " << e.what() << "\n";
        passed++;
    }

    // 🔄 Cleanup
    try {
        if (fs::exists(sourceFile)) fs::remove(sourceFile);
        if (fs::exists(destFile)) fs::remove(destFile);
    } catch (...) {
        std::cerr << "[WARN] Cleanup failed\n";
    }

    // 📊 Summary
    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return 0;
}
