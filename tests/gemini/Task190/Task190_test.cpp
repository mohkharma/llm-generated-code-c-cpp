#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

#include "../../../source/output/gemini/cpp/Task190_GEMINI_gemini-1.5-pro-001.cpp"

std::string normalize(const std::string& s) {
    std::stringstream in(s), out;
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream linestream(line);
        std::string word;
        bool first = true;
        while (linestream >> word) {
            if (!first) out << " ";
            out << word;
            first = false;
        }
        out << "\n";
    }
    return out.str();
}

bool runTest(const std::string& input, const std::string& expected, int testNum) {
    std::ofstream fout("file.txt");
    fout << input;
    fout.close();

    std::streambuf* orig_buf = std::cout.rdbuf();
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    solve();  // 👈 مهم: الحل فيه int solve()

    std::cout.rdbuf(orig_buf);
    std::string output = buffer.str();

    std::remove("file.txt");

    if (normalize(output) == normalize(expected)) {
        std::cout << "[✅] Passed: Test Case " << testNum << "\n";
        return true;
    } else {
        std::cout << "[❌] Failed: Test Case " << testNum << "\n";
        std::cout << "Expected:\n" << expected;
        std::cout << "\nGot:\n" << output << "\n";
        return false;
    }
}

int main() {
    int passed = 0, total = 0;

    total++;
    passed += runTest(
        "name age\nalice 21\nryan 30\n",
        "name alice ryan\nage 21 30\n",
        total
    );

    total++;
    passed += runTest(
        "x y\nz w\n",
        "x z\ny w\n",
        total
    );

    total++;
    passed += runTest(
        "a b c\nd e f\ng h i\n",
        "a d g\nb e h\nc f i\n",
        total
    );

    std::cout << "\nSummary: " << passed << "/" << total << " tests passed.\n";
    return 0;
}
