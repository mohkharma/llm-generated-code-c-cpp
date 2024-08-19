#include <algorithm>
#include <vector>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> merged(nums1.begin(), nums1.end());
        merged.insert(merged.end(), nums2.begin(), nums2.end());
        sort(merged.begin(), merged.end());
        int length = merged.size();
        if (length % 2 == 0) {
            return (merged[length / 2 - 1] + merged[length / 2]) / 2.0;
        } else {
            return merged[length / 2];
        }
    }
};