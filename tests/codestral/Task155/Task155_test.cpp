#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to run a test with given input and expected output strings
bool runTest(const string& inputStr, const string& expectedOutput) {
    // Parse input string into array
    istringstream iss(inputStr);
    int tempArr[1000];
    int n = 0;
    int num;
    while (iss >> num) {
        tempArr[n++] = num;
    }

    // Run heap sort
    heapSort(tempArr, n);

    // Capture output into stringstream
    ostringstream oss;
    for (int i = 0; i < n; i++) {
        oss << tempArr[i] << " ";
    }

    string actualOutput = oss.str();

    if (actualOutput == expectedOutput) {
        return true;
    } else {
        cerr << "Test failed.\nInput: \"" << inputStr << "\"\nExpected: \"" << expectedOutput
             << "\"\nGot:      \"" << actualOutput << "\"\n";
        return false;
    }
}

int main() {
    struct TestCase {
        string input;
        string expected;
    };

    TestCase tests[] = {
        {"12 11 13 5 6 7", "5 6 7 11 12 13 "},
        {"5 4 3 2 1", "1 2 3 4 5 "},
        {"10 9 8 7 6", "6 7 8 9 10 "},
        {"1 2 3 4 5", "1 2 3 4 5 "},
        {"9 8 7 6 5", "5 6 7 8 9 "}
    };

    bool allPassed = true;
    for (auto& test : tests) {
        if (!runTest(test.input, test.expected)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        cout << "All tests passed." << endl;
        return 0;
    } else {
        cout << "Some tests failed." << endl;
        return 1;
    }
}
