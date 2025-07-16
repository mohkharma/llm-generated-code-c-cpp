#include <iostream>
#include <uuid/uuid.h>
#include <cctype>
#include <string>

// الكود كما هو
std::string generateSessionId() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char str[37];
    uuid_unparse(uuid, str);
    return std::string(str);
}

// دالة تحقق صحة UUID4 (نفس شكل بايثون)
bool is_valid_uuid4(const std::string& uuid) {
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
    std::string session_id = generateSessionId();
    std::cout << "Generated session ID: " << session_id << std::endl;

    if (is_valid_uuid4(session_id)) {
        std::cout << "Test case 1 result: PASS" << std::endl;
    } else {
        std::cout << "Test case 1 result: FAIL" << std::endl;
    }

    return 0;
}
