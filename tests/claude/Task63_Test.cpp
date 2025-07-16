#include <iostream>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <boost/beast/core/detail/base64.hpp>

using json = nlohmann::json;

json process_request(const std::string& raw_data) {
    if (raw_data.empty()) {
        throw std::invalid_argument("Empty input");
    }

    // Base64 decode
    std::string decoded_data;
    decoded_data.resize(boost::beast::detail::base64::decoded_size(raw_data.size()));
    auto result = boost::beast::detail::base64::decode(&decoded_data[0], raw_data.data(), raw_data.size());
    decoded_data.resize(result.first);

    // Parse JSON
    json deserialized_data = json::parse(decoded_data);

    return deserialized_data;
}

// Simple test runner mimicking unittest test cases
void run_test(const std::string& test_name, const std::string& input, const json* expected = nullptr, bool expect_exception = false) {
    try {
        json output = process_request(input);
        if (expect_exception) {
            std::cout << test_name << ": FAIL (expected exception but got success)\n";
            return;
        }
        if (expected != nullptr && output == *expected) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL (output mismatch)\n";
        }
    } catch (const std::exception& e) {
        if (expect_exception) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL (unexpected exception: " << e.what() << ")\n";
        }
    }
}

int main() {
    using std::string;
    using json = nlohmann::json;

    const json expected1 = {{"name", "John Doe"}, {"age", 30}};
    run_test("test_valid_json", "eyJuYW1lIjogIkpvaG4gRG9lIiwgImFnZSI6IDMwfQ==", &expected1);

    run_test("test_empty_input", "", nullptr, true);

    run_test("test_invalid_base64", "invalid_base64_string", nullptr, true);

    run_test("test_malformed_json",
             "bmFtZSI6ICJKb2hufQ==", // base64 for name": "John}
             nullptr, true);

    const json expected_empty = json::object();
    run_test("test_base64_of_empty_json", "e30=", &expected_empty);

    const json expected_special = {{"key", "value_with_special_characters_!@#$%^&*()"}};
    run_test("test_json_with_special_characters", "eyJrZXkiOiAidmFsdWVfd2l0aF9zcGVjaWFsX2NoYXJhY3RlcnNfIUAjJCVeJiooKSJ9", &expected_special);

    const json expected_numeric = {{"value", 1234}};
    run_test("test_json_with_numeric_values", "eyJ2YWx1ZSI6IDEyMzR9", &expected_numeric);

    const json expected_boolean = {{"active", true}, {"verified", false}};
    run_test("test_json_with_boolean_values", "eyJhY3RpdmUiOiB0cnVlLCAidmVyaWZpZWQiOiBmYWxzZX0=", &expected_boolean);

    const json expected_null = {{"value", nullptr}};
    run_test("test_json_with_null_value", "eyJ2YWx1ZSI6IG51bGx9", &expected_null);

    const json expected_nested = {{"outer", {{"inner", "value"}}}};
    run_test("test_nested_json", "eyJvdXRlciI6IHsiaW5uZXIiOiAidmFsdWUifX0=", &expected_nested);

    return 0;
}

