#include <vector> // Include the vector header
#include <iostream> // Optional: for debugging or output

class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        std::vector<long long> sums(n + 1); // Use std::vector

        // Calculate the prefix sums
        for (int i = 0; i < n; i++) {
            sums[i + 1] = sums[i] + nums[i];
        }

        int res = 0;

        // Check for each range
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                long long rangeSum = sums[j + 1] - sums[i];
                if (lower <= rangeSum && rangeSum <= upper) {
                    res++;
                }
            }
        }
        return res;
    }
};