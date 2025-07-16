#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <json/json.h>
#include <cctype>

using namespace std;

// ----- Base64 encode/decode start -----
static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const unsigned char* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; i <4 ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = ( char_array_3[0] & 0xfc ) >> 2;
    char_array_4[1] = ( ( char_array_3[0] & 0x03 ) << 4 ) + ( ( char_array_3[1] & 0xf0 ) >> 4 );
    char_array_4[2] = ( ( char_array_3[1] & 0x0f ) << 2 ) + ( ( char_array_3[2] & 0xc0 ) >> 6 );
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';
  }

  return ret;
}

std::string base64_decode(const std::string& encoded_string) {
  int in_len = (int)encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

      char_array_3[0] = ( char_array_4[0] << 2 ) + ( ( char_array_4[1] & 0x30 ) >> 4 );
      char_array_3[1] = ( ( char_array_4[1] & 0xf ) << 4 ) + ( ( char_array_4[2] & 0x3c ) >> 2 );
      char_array_3[2] = ( ( char_array_4[2] & 0x3 ) << 6 ) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

    char_array_3[0] = ( char_array_4[0] << 2 ) + ( ( char_array_4[1] & 0x30 ) >> 4 );
    char_array_3[1] = ( ( char_array_4[1] & 0xf ) << 4 ) + ( ( char_array_4[2] & 0x3c ) >> 2 );
    char_array_3[2] = ( ( char_array_4[2] & 0x3 ) << 6 ) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
// ----- Base64 encode/decode end -----

// processRequest function
string processRequest(string req) {
    if (req.empty()) throw runtime_error("Empty input");

    string decoded_data;
    try {
        decoded_data = base64_decode(req);
    } catch (...) {
        throw runtime_error("Invalid base64");
    }

    Json::CharReaderBuilder reader;
    Json::Value deserialized_data;
    string errs;
    istringstream s(decoded_data);
    if (!Json::parseFromStream(reader, s, &deserialized_data, &errs)) {
        throw runtime_error("JSON decode error: " + errs);
    }

    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, deserialized_data);
}

// JSON equality checker
bool jsonEqual(const string& jsonStr, const Json::Value& expected) {
    Json::CharReaderBuilder reader;
    Json::Value actual;
    string errs;
    istringstream s(jsonStr);
    if (!Json::parseFromStream(reader, s, &actual, &errs)) {
        return false;
    }
    return actual == expected;
}

// Tests runner
void runTests() {
    int passCount = 0, failCount = 0;

    auto printResult = [&](const string& testName, bool passed, const string& reason="") {
        cout << testName << ": " << (passed ? "PASS" : "FAIL");
        if (!passed && !reason.empty()) cout << " (" << reason << ")";
        cout << endl;
        if (passed) passCount++; else failCount++;
    };

    // 1 - test_valid_json
    try {
        string raw_data = "eyJuYW1lIjogIkpvaG4gRG9lIiwgImFnZSI6IDMwfQ==";
        Json::Value expected;
        expected["name"] = "John Doe";
        expected["age"] = 30;
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, expected);
        printResult("test_valid_json", passed);
    } catch (...) {
        printResult("test_valid_json", false, "Exception thrown");
    }

    // 2 - test_empty_input
    try {
        string raw_data = "";
        processRequest(raw_data);
        printResult("test_empty_input", false, "Expected exception not thrown");
    } catch (...) {
        printResult("test_empty_input", true);
    }

    // 3 - test_invalid_base64
    try {
        string raw_data = "invalid_base64_string";
        processRequest(raw_data);
        printResult("test_invalid_base64", false, "Expected exception not thrown");
    } catch (...) {
        printResult("test_invalid_base64", true);
    }

    // 4 - test_malformed_json
    try {
        string malformed = base64_encode(reinterpret_cast<const unsigned char*>(R"(name": "John})"), (unsigned int)strlen(R"(name": "John})"));
        processRequest(malformed);
        printResult("test_malformed_json", false, "Expected exception not thrown");
    } catch (const runtime_error& e) {
        if (string(e.what()).find("JSON decode error") != string::npos) {
            printResult("test_malformed_json", true);
        } else {
            printResult("test_malformed_json", false, "Wrong exception type");
        }
    } catch (...) {
        printResult("test_malformed_json", false, "Wrong exception type");
    }

    // 5 - test_base64_of_empty_json
    try {
        Json::Value emptyObj = Json::Value(Json::objectValue);
        Json::StreamWriterBuilder writer;
        string emptyJson = Json::writeString(writer, emptyObj);
        string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(emptyJson.c_str()), (unsigned int)emptyJson.size());
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, emptyObj);
        printResult("test_base64_of_empty_json", passed);
    } catch (...) {
        printResult("test_base64_of_empty_json", false, "Exception thrown");
    }

    // 6 - test_json_with_special_characters
    try {
        Json::Value specialChars;
        specialChars["key"] = "value_with_special_characters_!@#$%^&*()";
        Json::StreamWriterBuilder writer;
        string jsonStr = Json::writeString(writer, specialChars);
        string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), (unsigned int)jsonStr.size());
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, specialChars);
        printResult("test_json_with_special_characters", passed);
    } catch (...) {
        printResult("test_json_with_special_characters", false, "Exception thrown");
    }

    // 7 - test_json_with_numeric_values
    try {
        Json::Value numericVal;
        numericVal["value"] = 1234;
        Json::StreamWriterBuilder writer;
        string jsonStr = Json::writeString(writer, numericVal);
        string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), (unsigned int)jsonStr.size());
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, numericVal);
        printResult("test_json_with_numeric_values", passed);
    } catch (...) {
        printResult("test_json_with_numeric_values", false, "Exception thrown");
    }

    // 8 - test_json_with_boolean_values
    try {
        Json::Value boolVal;
        boolVal["active"] = true;
        boolVal["verified"] = false;
        Json::StreamWriterBuilder writer;
        string jsonStr = Json::writeString(writer, boolVal);
        string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), (unsigned int)jsonStr.size());
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, boolVal);
        printResult("test_json_with_boolean_values", passed);
    } catch (...) {
        printResult("test_json_with_boolean_values", false, "Exception thrown");
    }

    // 9 - test_json_with_null_value
    try {
        Json::Value nullVal;
        nullVal["value"] = Json::nullValue;
        Json::StreamWriterBuilder writer;
        string jsonStr = Json::writeString(writer, nullVal);
        string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), (unsigned int)jsonStr.size());
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, nullVal);
        printResult("test_json_with_null_value", passed);
    } catch (...) {
        printResult("test_json_with_null_value", false, "Exception thrown");
    }

    // 10 - test_nested_json
    try {
        Json::Value nestedVal;
        nestedVal["outer"]["inner"] = "value";
        Json::StreamWriterBuilder writer;
        string jsonStr = Json::writeString(writer, nestedVal);
        string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), (unsigned int)jsonStr.size());
        string result = processRequest(raw_data);
        bool passed = jsonEqual(result, nestedVal);
        printResult("test_nested_json", passed);
    } catch (...) {
        printResult("test_nested_json", false, "Exception thrown");
    }

    cout << "\nSummary: Passed " << passCount << ", Failed " << failCount << endl;
}

int main() {
    runTests();
    return 0;
}
