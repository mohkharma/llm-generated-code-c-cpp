//error: ‘std::string’ {aka ‘class std::__cxx11::basic_string<char>’} has no member named ‘starts_with’
// #include <regex>
// #include <string>
//
// std::string cleanPhoneNumber(const std::string& phoneNumber) {
//     std::string cleanedNumber = std::regex_replace(phoneNumber, std::regex("\\D"), "");
//     if (cleanedNumber.starts_with("1")) {
//         cleanedNumber = cleanedNumber.substr(1);
//     }
//     return cleanedNumber;
// }

#include <regex>
#include <string>

std::string cleanPhoneNumber(const std::string& phoneNumber) {
    std::string cleanedNumber = std::regex_replace(phoneNumber, std::regex("\\D"), "");
    if (cleanedNumber.length() > 0 && cleanedNumber[0] == '1') {
        cleanedNumber = cleanedNumber.substr(1);
    }
    return cleanedNumber;
}
