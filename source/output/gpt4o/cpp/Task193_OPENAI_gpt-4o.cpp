#include <iostream>
#include <vector>

bool xorGame(std::vector<int>& nums) {
    int xorValue = 0;
    for (int num : nums) {
        xorValue ^= num;
    }
    return xorValue == 0 || nums.size() % 2 == 0;
}

int main() {
    //error: cannot bind non-const lvalue reference of type ‘std::vector<int>&’ to an rvalue of type ‘std::vector<int>’

    // std::cout << xorGame(std::vector<int>{1, 1, 2}) << std::endl;  // Output: 0 (false)
    // std::cout << xorGame(std::vector<int>{0, 1}) << std::endl;    // Output: 1 (true)
    // std::cout << xorGame(std::vector<int>{1, 2, 3}) << std::endl; // Output: 1 (true)

    std::vector<int> x1 = {1, 1, 2};
    std::vector<int> x2 = {0, 1};
    std::vector<int> x3 = {1, 2, 3};
    std::cout << xorGame(x1) << std::endl;  // Output: 0 (false)
    std::cout << xorGame(x2) << std::endl;    // Output: 1 (true)
    std::cout << xorGame(x3) << std::endl; // Output: 1 (true)
    return 0;
}