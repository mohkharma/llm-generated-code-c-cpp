#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, std::map<std::string, int>> productTable;
    productTable["apple"] = {{"price", 10}, {"stock", 100}};
    productTable["banana"] = {{"price", 5}, {"stock", 200}};
    productTable["orange"] = {{"price", 15}, {"stock", 50}};

    // ======= Test cases =======

    auto test_get_product = [&](const std::string& name, int expected_price, int expected_stock) {
        auto it = productTable.find(name);
        if (it == productTable.end()) {
            std::cout << "Test get product '" << name << "': FAIL (not found)\n";
            return false;
        }
        bool pass = (it->second["price"] == expected_price) && (it->second["stock"] == expected_stock);
        std::cout << "Test get product '" << name << "': " << (pass ? "PASS" : "FAIL") << "\n";
        if (!pass) {
            std::cout << "  Expected: price=" << expected_price << ", stock=" << expected_stock << "\n"
                      << "  Got: price=" << it->second["price"] << ", stock=" << it->second["stock"] << "\n";
        }
        return pass;
    };

    auto test_get_nonexistent = [&](const std::string& name) {
        auto it = productTable.find(name);
        bool pass = (it == productTable.end());
        std::cout << "Test get non-existent product '" << name << "': " << (pass ? "PASS" : "FAIL") << "\n";
        return pass;
    };

    int pass_count = 0;
    int fail_count = 0;

    if (test_get_product("apple", 10, 100)) pass_count++; else fail_count++;
    if (test_get_product("banana", 5, 200)) pass_count++; else fail_count++;
    if (test_get_product("orange", 15, 50)) pass_count++; else fail_count++;
    if (test_get_nonexistent("grape")) pass_count++; else fail_count++;

    std::cout << "Summary: " << pass_count << " passed, " << fail_count << " failed.\n";

    return 0;
}
