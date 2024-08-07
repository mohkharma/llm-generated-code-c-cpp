#include <deque>
#include <vector>

class Solution {
public:
    int shortestSubarray(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        int res = n + 1;
        std::deque<int> queue;
        for (int i = 0; i <= n; i++) {
            while (!queue.empty() && prefixSum[i] - prefixSum[queue.front()] >= k) {
                res = std::min(res, i - queue.front());
                queue.pop_front();
            }
            while (!queue.empty() && prefixSum[i] <= prefixSum[queue.back()]) {
                queue.pop_back();
            }
            queue.push_back(i);
        }
        return res <= n ? res : -1;
    }
};
