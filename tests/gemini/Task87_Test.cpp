#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

int binary_search(vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

bool file_exists_and_positive(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    double val = 0;
    file >> val;
    file.close();
    return val > 0;
}

int main() {
    vector<int> arr;
    for (int i = 0; i < 100000; i++) {
        arr.push_back(rand() % 100000);
    }
    sort(arr.begin(), arr.end()); // ضروري لترتيب المصفوفة قبل البحث

    int target = rand() % 100000;

    clock_t start = clock();
    int result = binary_search(arr, target);
    clock_t end = clock();

    double execution_time = (double)(end - start) / CLOCKS_PER_SEC;

    ofstream file("execution_time.txt");
    file << execution_time;
    file.close();

    cout << "Result: " << result << endl;

    bool pass = file_exists_and_positive("execution_time.txt") && (result >= -1 && result < (int)arr.size());

    if (pass) {
        cout << "Test case 1 result: PASS" << endl;
    } else {
        cout << "Test case 1 result: FAIL" << endl;
    }

    return 0;
}
