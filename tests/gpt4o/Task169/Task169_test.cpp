// Task169_Test.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// الحل باستخدام lower_bound وinsert
vector<int> countSmaller(vector<int>& nums) {
    vector<int> result(nums.size(), 0);
    vector<int> sortedList;
    for (int i = nums.size() - 1; i >= 0; i--) {
        auto it = lower_bound(sortedList.begin(), sortedList.end(), nums[i]);
        result[i] = distance(sortedList.begin(), it);
        sortedList.insert(it, nums[i]);
    }
    return result;
}

// تابع اختبار واحد
bool runTest(const vector<int>& input, const vector<int>& expected) {
    vector<int> in = input;
    vector<int> result = countSmaller(in);
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

// البرنامج الرئيسي للاختبار الذاتي
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
