#include <iostream>
#include <sstream>
#include <string>

#include "../../source/output/gemini/cpp/Task40_GEMINI_gemini-1.5-pro-001.cpp"  // Include the header for the function

int passed = 0;
int failed = 0;

void printResult(const std::string& name, bool success) {
    if (success) {
        std::cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << name << "\n";
        failed++;
    }
}

// نعيد توجيه cin و cout لمحاكاة POST input والتقاط الإخراج
void test_input_handling() {
    std::string simulated_input = "Ali\n";
    std::stringstream input(simulated_input);
    std::stringstream output;

    // حفظ cin و cout الأصليين
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    renderAndHandleForm();

    // إعادة cin و cout
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string output_str = output.str();
    bool ok = output_str.find("Username to update: Ali") != std::string::npos;
    printResult("test_input_handling", ok);
}

void test_form_renders_html() {
    std::stringstream input("TestUser\n");
    std::stringstream output;

    std::streambuf* cin_backup = std::cin.rdbuf();
    std::streambuf* cout_backup = std::cout.rdbuf();

    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    renderAndHandleForm();

    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string out = output.str();
    bool ok = out.find("<form method='post'>") != std::string::npos &&
              out.find("input type='text'") != std::string::npos;

    printResult("test_form_renders_html", ok);
}

int main() {
    test_form_renders_html();
    test_input_handling();

    std::cout << "\nTests passed: " << passed << "\n";
    std::cout << "Tests failed: " << failed << "\n";

    return failed == 0 ? 0 : 1;
}
