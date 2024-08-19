#include <iostream>
#include <string>
#include <cpp-base64/base64.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json processRequest(const std::string& rawData) {
    std::string decodedData = base64_decode(rawData);
    return json::parse(decodedData);
}