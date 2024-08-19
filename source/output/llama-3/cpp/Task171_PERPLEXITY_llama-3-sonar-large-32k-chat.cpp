#include <vector>  // Include the vector header
#include <algorithm> // Include the algorithm header for std::copy

class Solution {
public:
    int reversePairs(std::vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }

private:
    int mergeSort(std::vector<int>& nums, int left, int right) {
        if (left >= right) {
            return 0;
        }
        int mid = left + (right - left) / 2;
        int left_count = mergeSort(nums, left, mid);
        int right_count = mergeSort(nums, mid + 1, right);
        int merged_count = merge(nums, left, mid, right);
        return left_count + right_count + merged_count;
    }

    int merge(std::vector<int>& nums, int left, int mid, int right) {
        std::vector<int> temp(right - left + 1);
        int left_index = left, right_index = mid + 1, temp_index = 0, count = 0;

        // Count reverse pairs
        while (left_index <= mid && right_index <= right) {
            if (nums[left_index] <= 2 * nums[right_index]) {
                temp[temp_index++] = nums[left_index++];
            } else {
                temp[temp_index++] = nums[right_index++];
                count += mid - left_index + 1; // Count how many elements in left are greater
            }
        }

        // Copy remaining elements from the left half
        while (left_index <= mid) {
            temp[temp_index++] = nums[left_index++];
        }

        // Copy remaining elements from the right half
        while (right_index <= right) {
            temp[temp_index++] = nums[right_index++];
        }

        // Copy the sorted elements back into the original array
        std::copy(temp.begin(), temp.end(), nums.begin() + left);
        return count;
    }
};