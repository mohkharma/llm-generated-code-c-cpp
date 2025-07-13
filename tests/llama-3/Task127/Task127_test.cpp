#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <cstdlib>

namespace fs = std::filesystem;

int main() {
    int passed = 0;
    int total = 2;

    std::string execPath = "./Task130_test";
    std::string srcDir = "/path/to/source/directory";
    std::string dstDir = "/path/to/temporary/directory";
    std::string filename = "file.txt";
    std::string fullSrc = srcDir + "/" + filename;
    std::string fullDst = dstDir + "/" + filename;

    // ✅ Test 1: create source file and run test
    try {
        fs::create_directories(srcDir);
        fs::create_directories(dstDir);

        std::ofstream f(fullSrc);
        f << "Hello test content\n";
        f.close();

        int result = system((execPath + " > output1.txt 2>&1").c_str());

        std::ifstream out("output1.txt");
        std::stringstream ss;
        ss << out.rdbuf();
        std::string output = ss.str();

        if (result == 0 && output.find("has been copied") != std::string::npos && fs::exists(fullDst)) {
            std::cout << "[PASS] Test 1: file copied successfully\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 1: copy failed or output mismatch\n";
        }
    } catch (...) {
        std::cout << "[FAIL] Test 1: exception occurred\n";
    }

    // ✅ Test 2: remove source file and run again
    try {
        fs::remove(fullSrc);
        fs::remove(fullDst);

        int result = system((execPath + " > output2.txt 2>&1").c_str());

        std::ifstream out("output2.txt");
        std::stringstream ss;
        ss << out.rdbuf();
        std::string output = ss.str();

        if (result != 0 && output.find("not found") != std::string::npos) {
            std::cout << "[PASS] Test 2: missing file handled correctly\n";
            passed++;
        } else {
            std::cout << "[FAIL] Test 2: did not detect missing file\n";
        }
    } catch (...) {
        std::cout << "[FAIL] Test 2: exception occurred\n";
    }

    // 🔄 Cleanup
    try {
        fs::remove_all(srcDir);
        fs::remove_all(dstDir);
        fs::remove("output1.txt");
        fs::remove("output2.txt");
    } catch (...) {
        std::cerr << "[WARN] Cleanup failed\n";
    }

    // 📊 Summary
    std::cout << "------------------------\n";
    std::cout << "Passed " << passed << " out of " << total << " tests.\n";

    return 0;
}
