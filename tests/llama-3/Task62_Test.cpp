#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Function to parse JSON and return a pointer to json object.
// Returns nullptr on parse error.
json* parse_json_and_get_root(const std::string& json_str) {
    try {
        json* j = new json(json::parse(json_str));
        return j;
    } catch (json::parse_error&) {
        return nullptr;
    }
}

// Compare two json objects for equality.
// Returns true if equal, false otherwise.
bool compare_json(const json& a, const json& b) {
    return a == b;
}

// Helper to print test result.
void print_result(const std::string& test_name, bool passed) {
    std::cout << test_name << ": " << (passed ? "PASS" : "FAIL") << std::endl;
}

int main() {
    {
        std::string json_str = R"({"name": "John", "age": 30, "city": "New York"})";
        json* result = parse_json_and_get_root(json_str);
        print_result("test_valid_json", result && compare_json(*result, json::parse(json_str)));
        delete result;
    }
    {
        std::string json_str = "{}";
        json* result = parse_json_and_get_root(json_str);
        print_result("test_empty_json", result && compare_json(*result, json::parse(json_str)));
        delete result;
    }
    {
        std::string json_str = "[1, 2, 3, 4]";
        json* result = parse_json_and_get_root(json_str);
        print_result("test_json_with_array", result && compare_json(*result, json::parse(json_str)));
        delete result;
    }
    {
        std::string json_str = R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})";
        json* result = parse_json_and_get_root(json_str);
        print_result("test_json_with_nested_objects", result && compare_json(*result, json::parse(json_str)));
        delete result;
    }
    {
        std::string json_str = R"({"active": true, "verified": false})";
        json* result = parse_json_and_get_root(json_str);
        print_result("test_json_with_boolean_values", result && compare_json(*result, json::parse(json_str)));
        delete result;
    }
    {
        std::string json_str = R"({"value": null})";
        json* result = parse_json_and_get_root(json_str);
        print_result("test_json_with_null_value", result && compare_json(*result, json::parse(json_str)));
        delete result;
    }
    {
        std::string json_str = R"({"name": "John", "age": 30, "city": "New York")"; // missing closing brace
        json* result = parse_json_and_get_root(json_str);
        print_result("test_malformed_json_missing_bracket", result == nullptr);
        delete result;
    }
    {
        std::string json_str = R"({"name": "John", "age": 30,})"; // unexpected trailing comma
        json* result = parse_json_and_get_root(json_str);
        print_result("test_malformed_json_unexpected_comma", result == nullptr);
        delete result;
    }
    {
        std::string json_str = R"({name: "John", "age": 30})"; // unquoted key
        json* result = parse_json_and_get_root(json_str);
        print_result("test_malformed_json_unquoted_key", result == nullptr);
        delete result;
    }
    {
        std::string json_str = "Just a string, not JSON"; // not JSON at all
        json* result = parse_json_and_get_root(json_str);
        print_result("test_invalid_json_type", result == nullptr);
        delete result;
    }

    return 0;
}
