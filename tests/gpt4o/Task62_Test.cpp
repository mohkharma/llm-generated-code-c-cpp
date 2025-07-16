#include <iostream>
#include <string>
#include <json/json.h>

// دالة لتحليل JSON وإرجاع الجذر (Json::Value) أو قيمة فارغة إذا فشل
Json::Value parse_json_and_get_root(const std::string& jsonString) {
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    Json::Value root;
    std::string errs;

    bool parsingSuccessful = reader->parse(
        jsonString.c_str(), jsonString.c_str() + jsonString.size(),
        &root, &errs);

    if (!parsingSuccessful) {
        return Json::Value(); // فارغ يعني فشل
    }
    return root;
}

// دالة مقارنة بين JSON متوقعة وفعليه (Json::Value)
bool compare_json(const Json::Value& a, const Json::Value& b) {
    return a == b;
}

// دالة طباعة Json::Value كـ string
std::string json_to_string(const Json::Value& val) {
    Json::StreamWriterBuilder writer;
    writer["indentation"] = ""; // بدون تراجع مسافات لتسهيل المقارنة
    return Json::writeString(writer, val);
}

// تنفيذ اختبار معين واظهار النتيجة
void run_test(const std::string& test_name, const std::string& input_json, const Json::Value& expected, bool expect_empty) {
    Json::Value result = parse_json_and_get_root(input_json);

    if (expect_empty) {
        if (result.isNull() || result.empty()) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL (Expected parse failure, but got valid JSON)\n"
                      << "Got: " << json_to_string(result) << "\n";
        }
    } else {
        if (compare_json(result, expected)) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL\nExpected: " << json_to_string(expected)
                      << "\nGot:      " << json_to_string(result) << "\n";
        }
    }
}

int main() {
    run_test("test_valid_json",
             R"({"name": "John", "age": 30, "city": "New York"})",
             parse_json_and_get_root(R"({"name": "John", "age": 30, "city": "New York"})"),
             false);

    run_test("test_empty_json",
             R"({})",
             parse_json_and_get_root(R"({})"),
             false);

    run_test("test_json_with_array",
             R"([1, 2, 3, 4])",
             parse_json_and_get_root(R"([1, 2, 3, 4])"),
             false);

    run_test("test_json_with_nested_objects",
             R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})",
             parse_json_and_get_root(R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})"),
             false);

    run_test("test_json_with_boolean_values",
             R"({"active": true, "verified": false})",
             parse_json_and_get_root(R"({"active": true, "verified": false})"),
             false);

    run_test("test_json_with_null_value",
             R"({"value": null})",
             parse_json_and_get_root(R"({"value": null})"),
             false);

    run_test("test_malformed_json_missing_bracket",
             R"({"name": "John", "age": 30, "city": "New York")",
             Json::Value(),
             true);

    run_test("test_malformed_json_unexpected_comma",
             R"({"name": "John", "age": 30,})",
             Json::Value(),
             true);

    run_test("test_malformed_json_unquoted_key",
             R"({name: "John", "age": 30})",
             Json::Value(),
             true);

    run_test("test_invalid_json_type",
             "Just a string, not JSON",
             Json::Value(),
             true);

    return 0;
}
