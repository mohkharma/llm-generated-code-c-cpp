#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// الحل المُعطى كما هو دون تعديل
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> vec(n);

        for (int i = 0; i < n; i++) {
            vec[i] = {nums[i], i};
        }

        sort(vec.begin(), vec.end());

        vector<int> res(n, 0);

        for (int i = 0; i < n; i++) {
            auto it = lower_bound(vec.begin(), vec.end(), make_pair(nums[i], -1));
            res[vec[i].second] = it - vec.begin();
        }

        return res;
    }
};

// اختبار حالة واحدة
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

// البرنامج الرئيسي
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
