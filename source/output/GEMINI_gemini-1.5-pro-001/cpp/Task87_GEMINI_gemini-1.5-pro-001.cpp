#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int binarySearch(int arr[], int l, int r, int x)
{
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
 
int main(void)
{
    int arr[] = { 2, 3, 4, 10, 40 };
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    auto start = chrono::high_resolution_clock::now();
    int result = binarySearch(arr, 0, n - 1, x);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    ofstream output_file("execution_time.txt");
    if (result == -1)
        output_file << "Element is not present in array
";
    else
        output_file << "Element is present at index " << result << endl;
    output_file << "Time taken by function: "
           << duration.count() << " microseconds" << endl;
 
    return 0;
}