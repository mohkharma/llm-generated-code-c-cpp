#include <iostream>
#include <cstdlib>
#include <array>
#include <memory>
#include <string>

void runBashCommand(const std::string& command) {
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "An error occurred during execution." << std::endl;
        return;
    }

    std::array<char, 128> buffer;
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    std::cout << "Command output: " << result << std::endl;
}
