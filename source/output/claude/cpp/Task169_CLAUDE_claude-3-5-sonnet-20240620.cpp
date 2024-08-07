
#include <vector>

class Solution {
private:
    //error: ‘vector’ does not name a type
    // vector<int> count;
    std::vector<int> count;
    std::vector<int> indexes;
    std::vector<int> temp;

    void mergeSort(std::vector<int>& nums, int start, int end) {
        if (start >= end) return;

        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid);
        mergeSort(nums, mid + 1, end);

        merge(nums, start, mid, end);
    }

    void merge(std::vector<int>& nums, int start, int mid, int end) {
        for (int i = start; i <= end; i++) {
            temp[i] = indexes[i];
        }

        int i = start;
        int j = mid + 1;
        int k = start;

        while (i <= mid && j <= end) {
            if (nums[temp[i]] <= nums[temp[j]]) {
                indexes[k] = temp[i];
                count[temp[i]] += j - (mid + 1);
                i++;
            } else {
                indexes[k] = temp[j];
                j++;
            }
            k++;
        }

        while (i <= mid) {
            indexes[k] = temp[i];
            count[temp[i]] += end - mid;
            i++;
            k++;
        }
    }

public:
    std::vector<int> countSmaller(std::vector<int>& nums) {
        int n = nums.size();
        count.resize(n, 0);
        indexes.resize(n);
        temp.resize(n);

        for (int i = 0; i < n; i++) {
            indexes[i] = i;
        }

        mergeSort(nums, 0, n - 1);

        return count;
    }
};
