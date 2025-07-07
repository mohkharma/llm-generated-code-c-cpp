#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int maxSubArraySum(vector<int>& arr) {
    int maxGlobal = arr[0];
    int maxCurrent = arr[0];
    for (int i = 1; i < (int)arr.size(); i++) {
        maxCurrent = max(arr[i], maxCurrent + arr[i]);
        if (maxCurrent > maxGlobal) {
            maxGlobal = maxCurrent;
        }
    }
    return maxGlobal;
}

bool runTest(const string& inputStr, int expected) {
    stringstream input(inputStr);
    vector<int> arr;
    int num;
    // قراءة الأعداد حتى نهاية السطر
    while (input >> num) {
        arr.push_back(num);
    }

    if (arr.empty()) {
        cerr << "Test failed. Input empty.\n";
        return false;
    }

    int result = maxSubArraySum(arr);

    if (result == expected) {
        return true;
    } else {
        cerr << "Test failed.\nInput: " << inputStr
             << "\nExpected: " << expected
             << ", Got: " << result << endl;
        return false;
    }
}

int main() {
    int failed = 0;

    if (!runTest("1 2 3 4 5", 15)) failed++;
    if (!runTest("-1 -2 -3 -4 -5", -1)) failed++;
    if (!runTest("1 -2 3 4 -1 2 1 -5 4", 9)) failed++;
    if (!runTest("42", 42)) failed++;
    if (!runTest("0 0 0 0 0", 0)) failed++;

    // توليد سلسلة 1000 رقم واحد مفصولين بمسافة
    string largeInput;
    for (int i = 0; i < 1000; ++i) {
        largeInput += "1 ";
    }
    if (!runTest(largeInput, 1000)) failed++;

    if (!runTest("3 -1 4 -1 2 1 -5 4", 8)) failed++;
    if (!runTest("10 -1 -1 10 -1 10 -1", 27)) failed++;
    if (!runTest("1 -2 -3 4 5", 9)) failed++;
    if (!runTest("6 -1 -2 1 2", 6)) failed++;

    if (failed == 0) {
        cout << "All tests passed." << endl;
        return 0;
    } else {
        cout << failed << " tests failed." << endl;
        return 1;
    }
}
