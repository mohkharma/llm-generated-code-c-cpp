#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json parse_json_and_get_root(const std::string& json_string) {
    try {
        return json::parse(json_string);
    } catch (json::parse_error& e) {
        // لا يوجد nullptr في json، لذا نرجع json فارغ كإشارة للفشل
        return nullptr;  // أو يمكن json() أو json(nullptr) لكن nullptr أسهل في التحقق
    }
}

// دالة مساعدة للمقارنة والتقييم للتيست كيسز
bool compare_json(const json& j1, const json& j2) {
    return j1 == j2;
}

void run_test(const std::string& test_name, const std::string& input, const json& expected, bool expect_none) {
    json result = parse_json_and_get_root(input);

    if (expect_none) {
        if (result.is_null()) {
            std::cout << test_name << ": PASS\n";
        } else {
            std::cout << test_name << ": FAIL (expected null, got valid json)\n";
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
    run_test("test_valid_json", R"({"name": "John", "age": 30, "city": "New York"})",
             json::parse(R"({"name": "John", "age": 30, "city": "New York"})"), false);

    run_test("test_empty_json", R"({})", json::parse(R"({})"), false);

    run_test("test_json_with_array", R"([1, 2, 3, 4])", json::parse(R"([1, 2, 3, 4])"), false);

    run_test("test_json_with_nested_objects", R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})",
             json::parse(R"({"person": {"name": "Alice", "age": 25}, "city": "Wonderland"})"), false);

    run_test("test_json_with_boolean_values", R"({"active": true, "verified": false})",
             json::parse(R"({"active": true, "verified": false})"), false);

    run_test("test_json_with_null_value", R"({"value": null})", json::parse(R"({"value": null})"), false);

    run_test("test_malformed_json_missing_bracket", R"({"name": "John", "age": 30, "city": "New York")", json(), true);

    run_test("test_malformed_json_unexpected_comma", R"({"name": "John", "age": 30,})", json(), true);

    run_test("test_malformed_json_unquoted_key", R"({name: "John", "age": 30})", json(), true);

    run_test("test_invalid_json_type", "Just a string, not JSON", json(), true);

    return 0;
}
