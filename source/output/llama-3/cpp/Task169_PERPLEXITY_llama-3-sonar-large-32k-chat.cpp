#include <vector>
#include <algorithm>
#include <utility>

class Solution {
public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<std::pair<int, int>> vec(n);

        // Create a vector of pairs where each pair is (value, index)
        for (int i = 0; i < n; i++) {
            vec[i] = {nums[i], i};
        }

        // Sort the vector of pairs
        std::sort(vec.begin(), vec.end());

        std::vector<int> res(n, 0);

        // Count smaller elements
        for (int i = 0; i < n; i++) {
            auto it = std::lower_bound(vec.begin(), vec.end(), std::make_pair(nums[i], -1));
            res[vec[i].second] = it - vec.begin();
        }

        return res;
    }
};