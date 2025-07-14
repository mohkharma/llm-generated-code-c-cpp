#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

void read_and_sort_records_from_string(const std::string& data) {
    std::map<std::string, std::string> records;
    std::istringstream file(data);
    std::string line;

    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Trim whitespace from key
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);

            // Trim whitespace from value
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            records[key] = value;
        } else {
            std::cerr << "Warning: Skipping invalid line: " << line << std::endl;
        }
    }

    // Print sorted records
    for (const auto& record : records) {
        std::cout << record.first << ": " << record.second << std::endl;
    }
}

int main() {
    // Internal test data string (same as testFile.txt)
    std::string test_data =
        "zoo : value1\n"
        "book : value2\n"
        "door : value3\n"
        "tree : value4\n";

    // Redirect cout to a stringstream to capture output
    std::ostringstream output_capture;
    std::streambuf* old_cout_buf = std::cout.rdbuf(output_capture.rdbuf());

    read_and_sort_records_from_string(test_data);

    // Restore cout buffer
    std::cout.rdbuf(old_cout_buf);

    // Expected output (sorted by key)
    std::string expected_output =
        "book: value2\n"
        "door: value3\n"
        "tree: value4\n"
        "zoo: value1\n";

    // Compare output with expected output
    std::string actual_output = output_capture.str();

    if (actual_output == expected_output) {
        std::cout << "Test case result: PASS" << std::endl;
    } else {
        std::cout << "Test case result: FAIL" << std::endl;
        std::cout << "Expected output:\n" << expected_output << std::endl;
        std::cout << "Actual output:\n" << actual_output << std::endl;
    }

    return 0;
}
