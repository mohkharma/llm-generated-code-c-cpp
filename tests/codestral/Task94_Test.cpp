#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == std::string::npos || end == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

int main() {
    std::string data =
        "zoo : value1\n"
        "book : value2\n"
        "door : value3\n"
        "tree : value4\n";

    std::istringstream file(data);
    std::string line;
    std::vector<std::pair<std::string, std::string>> records;

    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));
            records.emplace_back(key, value);
        } else {
            std::cerr << "Skipping invalid line: " << line << std::endl;
        }
    }

    std::sort(records.begin(), records.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });

    for (const auto& [key, value] : records) {
        std::cout << key << ": " << value << std::endl;
    }

    return 0;
}
