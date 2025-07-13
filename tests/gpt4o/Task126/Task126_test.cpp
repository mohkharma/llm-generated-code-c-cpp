#include "../../../source/output/gpt4o/cpp/Task126_OPENAI_gpt-4o.cpp"
#include <iostream>
#include <sstream>
#include <string>

bool test_redirect(const std::string& input, const std::string& expected_output, const std::string& test_name) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(); // حفظ الإخراج الأصلي

    std::cout.rdbuf(buffer.rdbuf()); // إعادة توجيه الإخراج

    redirect(input); // استدعاء الدالة

    std::cout.rdbuf(oldCout); // إعادة std::cout كما كان

    std::string output = buffer.str();

    if (output.find(expected_output) != std::string::npos) {
        std::cout << "[PASS] " << test_name << std::endl;
        return true;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "Expected: \"" << expected_output << "\"\n";
        std::cout << "Got:      \"" << output << "\"\n";
        return false;
    }
}

int main() {
    int passed = 0;
    int total = 4;

    passed += test_redirect("home", "Redirect to Home Page", "Test Home");
    passed += test_redirect("about", "Redirect to About Page", "Test About");
    passed += test_redirect("contact", "Redirect to Contact Page", "Test Contact");
    passed += test_redirect("faq", "Page not found", "Test Invalid Input");

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of " << total << " tests." << std::endl;

    return 0;
}
