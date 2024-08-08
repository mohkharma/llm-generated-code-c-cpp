#include <vector>

bool xorGame(std::vector<int>& nums) {
    //error: expected unqualified-id before ‘xor’ token
    // int xor = 0;
    int xor1 = 0;
    for (int num : nums) {
        xor1 ^= num;
    }

    if (xor1 == 0) {
        return false;
    } else if (nums.size() % 2 == 0) {
        return false;
    } else {
        return true;
    }
}