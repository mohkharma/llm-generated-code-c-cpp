#include <vector>   // Include the vector header
#include <algorithm> // Include the algorithm header for std::max
#include <iostream>  // Optional: for debugging or output

class Solution {
public:
    int maxSum(std::vector<int>& nums, int k) { // Use std::vector
        int n = nums.size();
        std::vector<int> dp(n); // Use std::vector

        dp[0] = nums[0]; // Initialize the first element
        for (int i = 1; i < n; i++) {
            dp[i] = std::max(dp[i - 1], nums[i]); // Use std::max
            for (int j = 1; j <= std::min(i, k); j++) { // Use std::min
                if (i - j - 1 >= 0) { // Check bounds before accessing dp[i-j-1]
                    dp[i] = std::max(dp[i], dp[i - j - 1] + nums[i]); // Use std::max
                }
            }
        }
        return dp[n - 1]; // Return the maximum sum
    }
};
