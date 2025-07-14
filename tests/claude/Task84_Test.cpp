#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <cctype>

std::string generate_session_id() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (int i = 0; i < 32; ++i) {
        ss << std::setw(1) << dis(gen);
        if (i == 7 || i == 11 || i == 15 || i == 19) {
            ss << "-";
        }
    }

    return ss.str();
}

bool is_valid_uuid(const std::string& uuid) {
    if (uuid.size() != 36)
        return false;
    if (uuid[8] != '-' || uuid[13] != '-' || uuid[18] != '-' || uuid[23] != '-')
        return false;
    for (size_t i = 0; i < uuid.size(); ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23)
            continue;
        if (!std::isxdigit(uuid[i]))
            return false;
    }
    return true;
}

int main() {
    std::string session_id = generate_session_id();
    std::cout << "Generated session ID: " << session_id << std::endl;

    if (is_valid_uuid(session_id)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
