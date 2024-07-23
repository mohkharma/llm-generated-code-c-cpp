
#include <iostream>
#include <vector>
#include <numeric>

int findMissingNumber(const std::vector<int>& arr) {
    int n = arr.size() + 1;
    int expectedSum = n * (n + 1) / 2;
    int actualSum = std::accumulate(arr.begin(), arr.end(), 0);
    return expectedSum - actualSum;
}

int main() {
    std::vector<int> inputArray = {1, 2, 4, 6, 3, 7, 8};
    int missingNumber = findMissingNumber(inputArray);
    std::cout << "The missing number is: " << missingNumber << std::endl;
    return 0;
}
