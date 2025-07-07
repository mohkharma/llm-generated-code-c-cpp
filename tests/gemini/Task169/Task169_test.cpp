// Task169_Test.cpp
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

// الحل باستخدام Merge Sort مع تتبع الفهارس
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(n, 0);
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {nums[i], i};
        }
        mergeSort(arr, count, 0, n - 1);
        return count;
    }

private:
    void mergeSort(vector<pair<int, int>>& arr, vector<int>& count, int left, int right) {
        if (left >= right) return;
        int mid = (left + right) / 2;
        mergeSort(arr, count, left, mid);
        mergeSort(arr, count, mid + 1, right);
        merge(arr, count, left, mid, right);
    }

    void merge(vector<pair<int, int>>& arr, vector<int>& count, int left, int mid, int right) {
        int i = left, j = mid + 1, k = 0;
        vector<pair<int, int>> temp(right - left + 1);
        while (i <= mid && j <= right) {
            if (arr[i].first <= arr[j].first) {
                count[arr[i].second] += j - (mid + 1);
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            count[arr[i].second] += j - (mid + 1);
            temp[k++] = arr[i++];
        }
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        for (int p = 0; p < k; p++) {
            arr[left + p] = temp[p];
        }
    }
};

// اختبار نفس حالات بايثون
bool runTest(const vector<int>& input, const vector<int>& expected) {
    Solution sol;
    vector<int> in = input;
    vector<int> result = sol.countSmaller(in);
    if (result != expected) {
        cerr << "Test failed.\nInput: ";
        for (int x : input) cerr << x << " ";
        cerr << "\nExpected: ";
        for (int x : expected) cerr << x << " ";
        cerr << "\nGot: ";
        for (int x : result) cerr << x << " ";
        cerr << "\n";
        return false;
    }
    return true;
}

int main() {
    vector<pair<vector<int>, vector<int>>> testCases = {
        {{5, 2, 6, 1}, {2, 1, 1, 0}},
        {{-1}, {0}},
        {{-1, -1}, {0, 0}},
        {{1, 2, 3, 4}, {0, 0, 0, 0}},
        {{4, 3, 2, 1}, {3, 2, 1, 0}},
        {{2, 0, 1}, {2, 0, 0}},
        {{10, 3, 2, 5}, {3, 1, 0, 0}},
        {{1, 1, 1, 1}, {0, 0, 0, 0}},
        {{6, 1, 2, 7, 1}, {3, 0, 1, 1, 0}},
        {{5, 9, 2, 8, 6}, {1, 3, 0, 1, 0}}
    };

    bool allPassed = true;
    for (size_t i = 0; i < testCases.size(); ++i) {
        if (!runTest(testCases[i].first, testCases[i].second)) {
            cerr << "Test case " << (i + 1) << " failed.\n";
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All test cases passed successfully.\n";
    }

    return 0;
}
