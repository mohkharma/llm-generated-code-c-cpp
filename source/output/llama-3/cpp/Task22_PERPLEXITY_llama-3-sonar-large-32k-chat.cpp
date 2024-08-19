#include <any>
#include <vector>
#include <iostream>

//error: ‘Object’ was not declared in this scope
// std::vector<int> filterList(std::vector<Object> list) {
std::vector<int> filterList(std::vector<std::any> list) {
    std::vector<int> result;
    // for (auto obj : list) {
    for (const auto& obj : list) {
        // if (typeid(obj) == typeid(int)) {
        if (obj.type() == typeid(int)) {
            // result.push_back(obj);
            result.push_back(std::any_cast<int>(obj));

        }
    }
    return result;
}