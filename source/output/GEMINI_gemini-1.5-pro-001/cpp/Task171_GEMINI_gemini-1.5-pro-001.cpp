class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return 0;
        }
        int mid = n / 2;
        vector<int> left(nums.begin(), nums.begin() + mid);
        vector<int> right(nums.begin() + mid, nums.end());
        return reversePairs(left) + reversePairs(right) + mergeAndCount(left, right);
    }

private:
    int mergeAndCount(vector<int>& left, vector<int>& right) {
        int n1 = left.size();
        int n2 = right.size();
        vector<int> merged(n1 + n2);
        int i = 0;
        int j = 0;
        int k = 0;
        int count = 0;
        while (i < n1 && j < n2) {
            if (left[i] > 2 * right[j]) {
                count += n1 - i;
                j++;
            } else {
                i++;
            }
        }
        while (i < n1) {
            merged[k] = left[i];
            i++;
            k++;
        }
        while (j < n2) {
            merged[k] = right[j];
            j++;
            k++;
        }
        return count;
    }
};