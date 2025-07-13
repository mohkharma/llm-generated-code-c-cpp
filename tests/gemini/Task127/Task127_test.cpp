#include "../../../source/output/gemini/cpp/Task127_GEMINI_gemini-1.5-pro-001.cpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

int main() {
    int passed = 0;
    int total = 2;

    std::string sourceFile = "source_input.txt";

    // ✅ Test 1: Successful copy to temporary file
    try {
        std::ofstream out(sourceFile);
        out << "Hello from source file\nSecond line.";
        out.close();

        std::cout << "[INFO] Running processFile on existing file...\n";
        processFile(sourceFile);

        std::cout << "[PASS] Test 1: processed existing file without crash\n";
        passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 1: exception occurred while processing existing file\n";
    }

    // ✅ Test 2: File not found
    try {
        if (fs::exists(sourceFile)) fs::remove(sourceFile);

        std::cout << "[INFO] Running processFile on non-existent file...\n";
        processFile(sourceFile);

        std::cout << "[PASS] Test 2: handled missing file gracefully\n";
        passed++;
    } catch (...) {
        std::cout << "[FAIL] Test 2: exception thrown for missing file\n";
    }

    // 🔄 Cleanup
    try {
        if (fs::exists(sourceFile)) fs::remove(sourceFile);
    } catch (...) {
        std::cerr << "[WARN] Cleanup failed\n";
    }

    // 📊 Summary
    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return 0;
}
