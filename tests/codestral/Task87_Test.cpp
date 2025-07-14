#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

bool file_exists_and_positive(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    long long val = 0;
    file >> val;
    file.close();
    return val > 0;
}

int main() {
    int arr[] = {1, 3, 4, 10, 12, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;

    auto start = chrono::high_resolution_clock::now();
    int result = binarySearch(arr, 0, n - 1, x);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    ofstream myfile("execution_time.txt");
    myfile << duration.count();
    myfile.close();

    cout << "Result: " << result << endl;

    bool pass = (result == 3) && file_exists_and_positive("execution_time.txt");

    if (pass) {
        cout << "Test case 1 result: PASS" << endl;
    } else {
        cout << "Test case 1 result: FAIL" << endl;
    }

    return 0;
}
