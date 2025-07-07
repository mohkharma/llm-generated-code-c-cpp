#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int maxSubArraySum(vector<int>& arr) {
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];

    for (int i = 1; i < (int)arr.size(); i++) {
        maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

bool runTest(const string& inputStr, int expected) {
    stringstream input(inputStr);
    int n; input >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        input >> arr[i];
    }

    int result = maxSubArraySum(arr);

    stringstream output;
    output << "Maximum subarray sum: " << result << "\n";

    string expectedOutput = "Maximum subarray sum: " + to_string(expected) + "\n";

    if (output.str() == expectedOutput) {
        return true;
    } else {
        cerr << "Test failed.\nInput: " << inputStr
             << "Expected: " << expectedOutput
             << "Got: " << output.str() << endl;
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
