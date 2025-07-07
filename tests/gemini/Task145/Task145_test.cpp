#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> maxSubarraySum(vector<int> arr) {
    int maxSoFar = INT_MIN;
    int currentMax = 0;
    int startIndex = 0;
    int endIndex = 0;
    int j = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        currentMax += arr[i];

        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
            startIndex = j;
            endIndex = i;
        }

        if (currentMax < 0) {
            currentMax = 0;
            j = i + 1;
        }
    }

    return vector<int>(arr.begin() + startIndex, arr.begin() + endIndex + 1);
}

bool runTest(const string& inputStr, int expectedSum) {
    stringstream input(inputStr);
    int n; input >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        input >> arr[i];
    }

    vector<int> result = maxSubarraySum(arr);

    int sumResult = 0;
    for (int val : result) sumResult += val;

    if (sumResult == expectedSum) {
        return true;
    } else {
        cerr << "Test failed.\nInput: " << inputStr
             << "Expected sum: " << expectedSum
             << ", Got sum: " << sumResult << endl;
        return false;
    }
}

int main() {
    int failed = 0;

    if (!runTest("5 1 2 3 4 5", 15)) failed++;
    if (!runTest("5 -1 -2 -3 -4 -5", -1)) failed++;
    if (!runTest("9 1 -2 3 4 -1 2 1 -5 4", 9)) failed++;
    if (!runTest("1 42", 42)) failed++;
    if (!runTest("5 0 0 0 0 0", 0)) failed++;

    string largeInput = "1000";
    for (int i = 0; i < 1000; ++i) {
        largeInput += " 1";
    }
    if (!runTest(largeInput, 1000)) failed++;

    if (!runTest("8 3 -1 4 -1 2 1 -5 4", 8)) failed++;
    if (!runTest("7 10 -1 -1 10 -1 10 -1", 27)) failed++;
    if (!runTest("5 1 -2 -3 4 5", 9)) failed++;
    if (!runTest("5 6 -1 -2 1 2", 6)) failed++;

    if (failed == 0) {
        cout << "All tests passed." << endl;
        return 0;
    } else {
        cout << failed << " tests failed." << endl;
        return 1;
    }
}
