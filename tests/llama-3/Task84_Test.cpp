#include <iostream>
#include <uuid/uuid.h>
#include <regex>
#include <string>

// Generate a UUID string
std::string generate_uuid() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char uuid_str[37]; // 36 chars + null terminator
    uuid_unparse(uuid, uuid_str);
    return std::string(uuid_str);
}

// Validate UUID format using regex
bool is_valid_uuid(const std::string& uuid) {
    // UUID regex: 8-4-4-4-12 hex digits with dashes
    const std::regex uuid_regex(
        "^[a-f0-9]{8}-"
        "[a-f0-9]{4}-"
        "[a-f0-9]{4}-"
        "[a-f0-9]{4}-"
        "[a-f0-9]{12}$",
        std::regex::icase);
    return std::regex_match(uuid, uuid_regex);
}

void run_tests() {
    for (int i = 0; i < 5; i++) {
        std::string uuid = generate_uuid();
        bool length_ok = (uuid.length() == 36);
        bool format_ok = is_valid_uuid(uuid);
        std::cout << "Test " << i + 1 << ": " << uuid
                  << " | Length: " << (length_ok ? "OK" : "FAIL")
                  << " | Format: " << (format_ok ? "OK" : "FAIL") << "\n";
    }
}

int main() {
    run_tests();
    return 0;
}
