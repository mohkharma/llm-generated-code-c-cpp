#include "../../../source/output/llama-3/cpp/Task126_PERPLEXITY_llama-3-sonar-large-32k-chat.cpp"
#include <iostream>
#include <string>

#ifdef _WIN32
std::string buildCommand(const std::string& url) {
    return "start " + url;
}
#elif __APPLE__
std::string buildCommand(const std::string& url) {
    return "open " + url;
}
#else
std::string buildCommand(const std::string& url) {
    return "xdg-open " + url;
}
#endif

bool test_open_command(const std::string& url, const std::string& expected_command, const std::string& test_name) {
    std::string generated = buildCommand(url);

    if (generated == expected_command) {
        std::cout << "[PASS] " << test_name << std::endl;
        return true;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        std::cout << "Expected: \"" << expected_command << "\"\n";
        std::cout << "Got:      \"" << generated << "\"\n";
        return false;
    }
}

int main() {
    int passed = 0;
    int total = 1;

#ifdef _WIN32
    passed += test_open_command("https://www.google.com", "start https://www.google.com", "Test Google on Windows");
#elif __APPLE__
    passed += test_open_command("https://www.google.com", "open https://www.google.com", "Test Google on macOS");
#else
    passed += test_open_command("https://www.google.com", "xdg-open https://www.google.com", "Test Google on Linux");
#endif

    std::cout << "------------------------" << std::endl;
    std::cout << "Passed " << passed << " out of " << total << " tests." << std::endl;

    return 0;
}
