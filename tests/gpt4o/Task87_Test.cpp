#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace std::chrono;

int binarySearch(const vector<int>& arr, int x) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

bool file_exists_and_not_empty(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    string content;
    getline(file, content);
    file.close();
    return !content.empty();
}

int main() {
    vector<int> arr = {2, 3, 4, 10, 40};
    int x = 10;
    auto start = high_resolution_clock::now();
    int result = binarySearch(arr, x);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();

    const string filename = "binary_search_execution_time.txt";
    ofstream tempFile(filename);
    tempFile << "Execution time: " << duration << " microseconds";
    tempFile.close();

    cout << "Result: " << result << endl;

    bool pass = (result == 3) && file_exists_and_not_empty(filename);

    if (pass) {
        cout << "Test case 1 result: PASS" << endl;
    } else {
        cout << "Test case 1 result: FAIL" << endl;
    }

    return 0;
}
