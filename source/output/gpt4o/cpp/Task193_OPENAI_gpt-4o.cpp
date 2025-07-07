#include <iostream>
#include <vector>

bool xorGame(std::vector<int>& nums) {
    int xorValue = 0;
    for (int num : nums) {
        xorValue ^= num;
    }
    return xorValue == 0 || nums.size() % 2 == 0;
}

