#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp> // تحتاج إضافة json.hpp من مكتبة nlohmann/json
// https://github.com/nlohmann/json

using json = nlohmann::json;

// Simple base64 decode function (RFC4648) adapted for demo purpose:
static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
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

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

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

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

json process_request(const std::string& request) {
    if (request.empty()) {
        throw std::invalid_argument("Input is empty");
    }
    // raw_data assumed UTF-8 string (std::string)
    // Base64 decode
    std::string decoded;
    try {
        decoded = base64_decode(request);
    } catch (...) {
        throw std::invalid_argument("Invalid base64");
    }
    if (decoded.empty() && !request.empty()) {
        // base64 decode failure
        throw std::invalid_argument("Invalid base64");
    }
    // Deserialize JSON
    try {
        return json::parse(decoded);
    } catch (json::parse_error& e) {
        throw; // propagate parse error
    }
}

// Helper function to compare json objects (order independent)
bool json_equal(const json& j1, const json& j2) {
    return j1 == j2;
}

// Test runner
void run_test(const std::string& test_name, const std::string& raw_data,
              const json* expected_output = nullptr,
              const std::string& expected_exception = "") {
    std::cout << test_name << ": ";
    try {
        json result = process_request(raw_data);
        if (!expected_exception.empty()) {
            // Expected an exception but none thrown
            std::cout << "FAIL (expected exception " << expected_exception << ")\n";
            return;
        }
        if (expected_output != nullptr) {
            if (json_equal(result, *expected_output)) {
                std::cout << "PASS\n";
            } else {
                std::cout << "FAIL (output mismatch)\n";
            }
        } else {
            // No expected output given
            std::cout << "FAIL (no expected output)\n";
        }
    } catch (const std::exception& e) {
        if (!expected_exception.empty()) {
            // Check if exception type matches expected
            std::string what = e.what();
            if (expected_exception == "Exception") {
                // Generic exception expected
                std::cout << "PASS\n";
            } else if (expected_exception == "json.JSONDecodeError") {
                // Check if it's JSON parse error (nlohmann::json throws parse_error)
                if (std::string(typeid(e).name()).find("parse_error") != std::string::npos
                    || what.find("parse") != std::string::npos) {
                    std::cout << "PASS\n";
                } else {
                    std::cout << "FAIL (wrong exception: " << what << ")\n";
                }
            } else {
                std::cout << "FAIL (wrong exception: " << what << ")\n";
            }
        } else {
            // Unexpected exception thrown
            std::cout << "FAIL (unexpected exception: " << e.what() << ")\n";
        }
    } catch (...) {
        std::cout << "FAIL (unknown exception)\n";
    }
}

int main() {
    // test_valid_json
    json expected_valid_json = {{"name", "John Doe"}, {"age", 30}};
    run_test("test_valid_json", "eyJuYW1lIjogIkpvaG4gRG9lIiwgImFnZSI6IDMwfQ==", &expected_valid_json);

    // test_empty_input
    run_test("test_empty_input", "", nullptr, "Exception");

    // test_invalid_base64
    run_test("test_invalid_base64", "invalid_base64_string", nullptr, "Exception");

    // test_malformed_json
    std::string malformed_base64 = "bmFtZSI6ICJKb2hufQ==";
    run_test("test_malformed_json", malformed_base64, nullptr, "json.JSONDecodeError");

    // test_base64_of_empty_json
    json expected_empty_json = json::object();
    std::string empty_json_b64 = "e30=";
    run_test("test_base64_of_empty_json", empty_json_b64, &expected_empty_json);

    // test_json_with_special_characters
    json expected_special_chars = {{"key", "value_with_special_characters_!@#$%^&*()"}};
    std::string special_chars_b64 = "eyJrZXkiOiAidmFsdWVfd2l0aF9zcGVjaWFsX2NoYXJhY3RlcnNfIUAjJCVeJiooKSJ9";
    run_test("test_json_with_special_characters", special_chars_b64, &expected_special_chars);

    // test_json_with_numeric_values
    json expected_numeric = {{"value", 1234}};
    std::string numeric_b64 = "eyJ2YWx1ZSI6IDEyMzR9";
    run_test("test_json_with_numeric_values", numeric_b64, &expected_numeric);

    // test_json_with_boolean_values
    json expected_boolean = {{"active", true}, {"verified", false}};
    std::string boolean_b64 = "eyJhY3RpdmUiOiB0cnVlLCAidmVyaWZpZWQiOiBmYWxzZX0=";
    run_test("test_json_with_boolean_values", boolean_b64, &expected_boolean);

    // test_json_with_null_value
    json expected_null = {{"value", nullptr}};
    std::string null_b64 = "eyJ2YWx1ZSI6IG51bGx9";
    run_test("test_json_with_null_value", null_b64, &expected_null);

    // test_nested_json
    json expected_nested = {{"outer", {{"inner", "value"}}}};
    std::string nested_b64 = "eyJvdXRlciI6IHsiaW5uZXIiOiAidmFsdWUifX0=";
    run_test("test_nested_json", nested_b64, &expected_nested);

    return 0;
}
