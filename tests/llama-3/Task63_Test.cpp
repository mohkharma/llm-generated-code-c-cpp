#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// --- Base64 encode/decode functions start ---
static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

static inline bool is_base64(unsigned char c) {
  return (std::isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const unsigned char* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0, j = 0;
  unsigned char char_array_3[3], char_array_4[4];

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
  int i = 0, j = 0, in_ = 0;
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
// --- Base64 encode/decode functions end ---

// processRequest كما في كودك الأصلي
json processRequest(const std::string& request) {
    std::string raw_data = request;
    std::string decoded_data = base64_decode(raw_data);
    return json::parse(decoded_data);
}

// للمقارنة بين النتيجة المتوقعة والنتيجة الحقيقية
bool jsonEqual(const json& actual, const json& expected) {
    return actual == expected;
}

// التست كيسز (بنفس حالات بايثون بالضبط)
void runTests() {
    int passCount = 0, failCount = 0;

    auto printResult = [&](const std::string& testName, bool passed, const std::string& reason="") {
        std::cout << testName << ": " << (passed ? "PASS" : "FAIL");
        if (!passed && !reason.empty()) std::cout << " (" << reason << ")";
        std::cout << std::endl;
        if (passed) passCount++; else failCount++;
    };

    // 1 - test_valid_json
    try {
        std::string raw_data = "eyJuYW1lIjogIkpvaG4gRG9lIiwgImFnZSI6IDMwfQ==";
        json expected = {{"name", "John Doe"}, {"age", 30}};
        json result = processRequest(raw_data);
        printResult("test_valid_json", jsonEqual(result, expected));
    } catch (...) {
        printResult("test_valid_json", false, "Exception thrown");
    }

    // 2 - test_empty_input
    try {
        std::string raw_data = "";
        processRequest(raw_data);
        printResult("test_empty_input", false, "Expected exception not thrown");
    } catch (...) {
        printResult("test_empty_input", true);
    }

    // 3 - test_invalid_base64
    try {
        std::string raw_data = "invalid_base64_string";
        processRequest(raw_data);
        printResult("test_invalid_base64", false, "Expected exception not thrown");
    } catch (...) {
        printResult("test_invalid_base64", true);
    }

    // 4 - test_malformed_json
    try {
        std::string malformed = base64_encode(reinterpret_cast<const unsigned char*>(R"(name": "John})"), strlen(R"(name": "John})"));
        processRequest(malformed);
        printResult("test_malformed_json", false, "Expected exception not thrown");
    } catch (const nlohmann::json::parse_error&) {
        printResult("test_malformed_json", true);
    } catch (...) {
        printResult("test_malformed_json", false, "Wrong exception type");
    }

    // 5 - test_base64_of_empty_json
    try {
        json emptyObj = json::object();
        std::string emptyJsonStr = emptyObj.dump();
        std::string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(emptyJsonStr.c_str()), emptyJsonStr.size());
        json result = processRequest(raw_data);
        printResult("test_base64_of_empty_json", jsonEqual(result, emptyObj));
    } catch (...) {
        printResult("test_base64_of_empty_json", false, "Exception thrown");
    }

    // 6 - test_json_with_special_characters
    try {
        json specialChars = {{"key", "value_with_special_characters_!@#$%^&*()"}};
        std::string jsonStr = specialChars.dump();
        std::string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), jsonStr.size());
        json result = processRequest(raw_data);
        printResult("test_json_with_special_characters", jsonEqual(result, specialChars));
    } catch (...) {
        printResult("test_json_with_special_characters", false, "Exception thrown");
    }

    // 7 - test_json_with_numeric_values
    try {
        json numericVal = {{"value", 1234}};
        std::string jsonStr = numericVal.dump();
        std::string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), jsonStr.size());
        json result = processRequest(raw_data);
        printResult("test_json_with_numeric_values", jsonEqual(result, numericVal));
    } catch (...) {
        printResult("test_json_with_numeric_values", false, "Exception thrown");
    }

    // 8 - test_json_with_boolean_values
    try {
        json boolVal = {{"active", true}, {"verified", false}};
        std::string jsonStr = boolVal.dump();
        std::string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), jsonStr.size());
        json result = processRequest(raw_data);
        printResult("test_json_with_boolean_values", jsonEqual(result, boolVal));
    } catch (...) {
        printResult("test_json_with_boolean_values", false, "Exception thrown");
    }

    // 9 - test_json_with_null_value
    try {
        json nullVal = {{"value", nullptr}};
        std::string jsonStr = nullVal.dump();
        std::string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), jsonStr.size());
        json result = processRequest(raw_data);
        printResult("test_json_with_null_value", jsonEqual(result, nullVal));
    } catch (...) {
        printResult("test_json_with_null_value", false, "Exception thrown");
    }

    // 10 - test_nested_json
    try {
        json nestedVal = {{"outer", {{"inner", "value"}}}};
        std::string jsonStr = nestedVal.dump();
        std::string raw_data = base64_encode(reinterpret_cast<const unsigned char*>(jsonStr.c_str()), jsonStr.size());
        json result = processRequest(raw_data);
        printResult("test_nested_json", jsonEqual(result, nestedVal));
    } catch (...) {
        printResult("test_nested_json", false, "Exception thrown");
    }

    std::cout << "\nSummary: Passed " << passCount << ", Failed " << failCount << std::endl;
}

int main() {
    runTests();
    return 0;
}
