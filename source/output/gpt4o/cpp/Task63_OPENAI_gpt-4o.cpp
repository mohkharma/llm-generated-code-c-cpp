#include <iostream>
#include <string>
#include <vector>
#include <cpp-base64/base64.h>
#include "json/json.h"

using namespace std;

string processRequest(string req);
// Json::Value base64_decode(string const& encoded_string);
// Function Definitions

// string base64_decode(string const& encoded_string) {
string base64_decode(const std::string&  encoded_string) {
    // vector<unsigned char> decoded = base64::decode(encoded_string);
    // vector<unsigned char> decoded = base64_decode(encoded_string);
    std::string decoded = base64_decode(encoded_string, false);
    return string(decoded.begin(), decoded.end());
}
// Example usage
int main() {
    Json::Value data;
    data["key"] = "value";
    Json::StreamWriterBuilder writer;
    string json = Json::writeString(writer, data);
    string encoded = base64_encode(reinterpret_cast<const unsigned char*>(json.c_str()), json.length());
    string result = processRequest(encoded);
    cout << result << endl;
    return 0;
}

string processRequest(string req) {
    // Step 1: Retrieve the raw_data from the request, ensuring it is encoded in UTF-8

    //error: call of overloaded ‘base64_decode(std::string&)’ is ambiguous
    // Step 2: Decode the raw_data using Base64
    // string decoded_data = base64_decode(req);
    string decoded_data = base64_decode(req, false);

    // Step 3: Deserialize the decoded data into its original format (e.g., JSON)
    Json::CharReaderBuilder reader;
    Json::Value deserialized_data;
    string errs;
    istringstream s(decoded_data);
    if (!Json::parseFromStream(reader, s, &deserialized_data, &errs)) {
        cout << "Error decoding JSON: " << errs << endl;
        return "";
    }

    // Step 4: Store the deserialized data in a variable
    Json::Value stored_data = deserialized_data;

    // Step 5: Return the stored data
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, stored_data);
}

