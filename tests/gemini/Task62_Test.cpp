#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// دالة استخراج root element من JSON string
json getRootElement(const std::string& jsonString) {
    try {
        return json::parse(jsonString);
    } catch (const json::exception& e) {
        // يمكنك تعطيل طباعة الخطأ لو تريد
        // std::cerr << "Invalid JSON string: " << e.what() << std::endl;
        return nullptr; // يعبر عن null في nlohmann::json
    }
}

// دالة مقارنة بين JSON متوقعة ونتيجة الفعلية
bool compare_json(const json& a, const json& b) {
    return a == b;
}

// دالة لتنفيذ اختبار معين وعرض النتيجة
void run_test(const std::string& test_name, const std::string& input_json, const json& expected, bool expect_null) {
    json result = getRootElement(input_json);

    if (expect_null) {
        if (result.is_null()) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL (Expected null, got valid JSON)\n";
        }
    } else {
        if (compare_json(result, expected)) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL\nExpected: " << expected.dump() << "\nGot:      " << result.dump() << "\n";
        }
    }
}

int main() {
    run_test("test_valid_json",
             R"({"name": "John", "age": 30, "city": "New York"})",
             json::parse(R"({"name": "John", "age": 30, "city": "New York"})"),
             false);

    run_test("test_empty_json",
             R"({})",
             json::parse(R"({})"),
             false);

    run_test("test_json_with_array",
             R"([1, 2, 3, 4])",
             json::parse(R"([1, 2, 3, 4])"),
             false);

    run_test("test_json_with_nested_objects",
             R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})",
             json::parse(R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})"),
             false);

    run_test("test_json_with_boolean_values",
             R"({"active": true, "verified": false})",
             json::parse(R"({"active": true, "verified": false})"),
             false);

    run_test("test_json_with_null_value",
             R"({"value": null})",
             json::parse(R"({"value": null})"),
             false);

    run_test("test_malformed_json_missing_bracket",
             R"({"name": "John", "age": 30, "city": "New York")",
             json(),
             true);

    run_test("test_malformed_json_unexpected_comma",
             R"({"name": "John", "age": 30,})",
             json(),
             true);

    run_test("test_malformed_json_unquoted_key",
             R"({name: "John", "age": 30})",
             json(),
             true);

    run_test("test_invalid_json_type",
             "Just a string, not JSON",
             json(),
             true);

    return 0;
}
