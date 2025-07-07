#include <iostream>
#include <string>
#include <regex>

std::string clean_phone_number(const std::string& phone_number) {
  std::string cleaned_number = std::regex_replace(phone_number, std::regex("[^0-9]"), "");
  if (cleaned_number.length() == 11 && cleaned_number[0] == '1') {
    return cleaned_number.substr(1);
  }
  return (cleaned_number.length() == 10) ? cleaned_number : "";
}
