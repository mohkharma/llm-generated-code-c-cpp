#include <vector>

class Solution {
public:
    bool xorGame(std::vector<int>& nums) {
        int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }

        return xorSum == 0 || nums.size() % 2 == 0;
    }
};
