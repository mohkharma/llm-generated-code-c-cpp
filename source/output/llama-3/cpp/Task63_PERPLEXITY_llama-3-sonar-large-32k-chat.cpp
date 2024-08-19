#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
//fixed manually
#include <cpp-base64/base64.h>
using json = nlohmann::json;

json processRequest(const std::string& request) {
    std::string raw_data = request;
    std::string decoded_data = base64_decode(raw_data); // Use the appropriate function from the library
    return json::parse(decoded_data);
}

int main() {
    // Example usage
    std::string request = "eyJ1c2VybmFtZSI6ICJhZG1pbiIsICJwYXNzd29yZCI6ICJwYXNzd29yZDEyMyJ9"; // Example Base64 encoded JSON
    json result = processRequest(request);
    std::cout << result.dump(4) << std::endl; // Pretty print the JSON
    return 0;
}