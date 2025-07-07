#include <iostream>
#include <vector>
#include <sstream>
#include <string>

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// This function runs a single test given an input string and expected output string
bool runTest(const std::string& inputStr, const std::string& expectedOutput) {
    std::istringstream iss(inputStr);
    std::vector<int> arr;
    int num;
    while (iss >> num) {
        arr.push_back(num);
    }

    heapSort(arr);

    std::ostringstream oss;
    for (int val : arr) {
        oss << val << " ";
    }

    std::string actualOutput = oss.str();

    if (actualOutput == expectedOutput) {
        return true;
    } else {
        std::cerr << "Test failed.\nInput: \"" << inputStr << "\"\nExpected: \"" << expectedOutput
                  << "\"\nGot:      \"" << actualOutput << "\"\n";
        return false;
    }
}

int main() {
    // Define multiple test cases exactly like Python unittest style but inline
    struct TestCase {
        std::string input;
        std::string expected;
    };

    TestCase tests[] = {
        {"5 12 11 13 14 15", "5 11 12 13 14 15 "},
        {"4 10 3 5 1", "1 3 4 5 10 "},
        {"1 2 3 4 5", "1 2 3 4 5 "},
        {"5 4 3 2 1", "1 2 3 4 5 "},
        {"10 9 8 7 6 5 4 3 2 1", "1 2 3 4 5 6 7 8 9 10 "}
    };

    bool allPassed = true;
    for (const auto& test : tests) {
        if (!runTest(test.input, test.expected)) {
            allPassed = false;
        }
    }

    if (allPassed) {
        std::cout << "All tests passed." << std::endl;
        return 0;
    } else {
        std::cout << "Some tests failed." << std::endl;
        return 1;
    }
}
