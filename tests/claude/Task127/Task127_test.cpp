#include "../../../source/output/claude/cpp/Task127_CLAUDE_claude-3-5-sonnet-20240620.cpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

int main() {
    int passed = 0;
    int total = 4; // عدّل حسب عدد الاختبارات

    std::string tempDir = "./temp_test_dir";
    std::string sourceFile = "source.txt";
    std::string tempFile = tempDir + "/temp_copy.txt";

    // ✅ Test 1: Successful copy
    try {
        std::ofstream src(sourceFile);
        src << "Hello, file!\nSecond line.";
        src.close();

        fs::create_directory(tempDir);
        copyFile(sourceFile, tempFile);

        std::ifstream f1(sourceFile), f2(tempFile);
        std::stringstream s1, s2;
        s1 << f1.rdbuf();
        s2 << f2.rdbuf();

        if (s1.str() == s2.str()) {
            std::cout << "[PASS] Test 1: successful file copy\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 1: file content mismatch\n";
        }
    } catch (...) {
        std::cout << "[FAIL] Test 1: unexpected exception\n";
    }

    // ✅ Test 2: Source file does not exist
    try {
        std::string missingSource = "non_existent_file.txt";
        copyFile(missingSource, tempFile);
        std::cout << "[FAIL] Test 2: expected error for missing source file\n";
    } catch (...) {
        std::cout << "[PASS] Test 2: handled missing source file\n";
        passed++;
    }

    // ✅ Test 3: Cannot write to destination (simulate by making directory read-only)
    try {
        fs::permissions(tempDir, fs::perms::owner_read, fs::perm_options::replace);
        copyFile(sourceFile, tempFile);
        std::cout << "[FAIL] Test 3: expected permission error\n";
    } catch (...) {
        std::cout << "[PASS] Test 3: handled write permission error\n";
        passed++;
    }
    fs::permissions(tempDir, fs::perms::owner_all); // restore

    // ✅ Test 4: Creating directory fails
    std::string lockedDir = "/root/locked_test_dir";
    try {
        copyFile(sourceFile, lockedDir + "/temp.txt");
        std::cout << "[FAIL] Test 4: expected error for directory creation\n";
    } catch (...) {
        std::cout << "[PASS] Test 4: handled error during directory creation\n";
        passed++;
    }

    // 🔄 Cleanup
    try {
        if (fs::exists(tempFile)) fs::remove(tempFile);
        if (fs::exists(sourceFile)) fs::remove(sourceFile);
        if (fs::exists(tempDir)) fs::remove_all(tempDir);
    } catch (...) {
        std::cerr << "[WARN] Cleanup failed\n";
    }

    // ✅ Summary
    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return 0;
}
