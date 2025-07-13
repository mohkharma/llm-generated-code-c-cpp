#include "../../../source/output/codestral/cpp/Task127_MISTRAL_codestral-latest.cpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

int main() {
    int passed = 0;
    int total = 2;

    std::string sourceFile = "source_file.txt";
    std::string destFile = "destination_file.txt";

    // ✅ Test 1: successful copy
    try {
        std::ofstream src(sourceFile);
        src << "Test file content\nLine 2.";
        src.close();

        copyFile(sourceFile, destFile);

        std::ifstream srcFile(sourceFile), dstFile(destFile);
        std::stringstream srcContent, dstContent;
        srcContent << srcFile.rdbuf();
        dstContent << dstFile.rdbuf();

        if (fs::exists(destFile) && srcContent.str() == dstContent.str()) {
            std::cout << "[PASS] Test 1: successful file copy\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 1: file content mismatch or destination file missing\n";
        }

    } catch (...) {
        std::cout << "[FAIL] Test 1: exception occurred during copy\n";
    }

    // ✅ Test 2: source file does not exist
    try {
        if (fs::exists(sourceFile)) fs::remove(sourceFile);
        if (fs::exists(destFile)) fs::remove(destFile);

        copyFile(sourceFile, destFile);

        if (!fs::exists(destFile)) {
            std::cout << "[PASS] Test 2: handled missing source file\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 2: destination file was unexpectedly created\n";
        }
    } catch (...) {
        std::cout << "[FAIL] Test 2: unexpected exception for missing source file\n";
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
