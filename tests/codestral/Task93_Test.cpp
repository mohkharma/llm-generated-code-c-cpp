#include <iostream>
#include <string>
#include <map>
#include <sstream>

void read_and_sort_records_from_string(const std::string& data) {
    std::map<std::string, std::string> records;
    std::istringstream file(data);
    std::string line;

    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            records[key] = value;
        } else {
            std::cerr << "Warning: skipping invalid line: " << line << std::endl;
        }
    }

    for (const auto& record : records) {
        std::cout << record.first << ": " << record.second << std::endl;
    }
}

int main() {
    const std::string test_data =
        "zoo : value1\n"
        "book : value2\n"
        "door : value3\n"
        "tree : value4\n";

    read_and_sort_records_from_string(test_data);
    return 0;
}
