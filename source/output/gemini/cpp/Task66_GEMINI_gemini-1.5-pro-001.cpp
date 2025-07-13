#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>

void executeBashCommand(const std::string& command) {
  try {
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
      throw std::runtime_error("popen() failed!");
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
      result += buffer;
    }

    std::cout << result;
  } catch (const std::runtime_error& e) {
    std::cerr << "Error executing command: " << e.what() << std::endl;
  }
}
