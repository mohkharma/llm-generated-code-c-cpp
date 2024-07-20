#include <iostream>
#include <cmath>

int binaryArrayToNumber(int arr[], int size) {
    int num = 0;
    for (int i = 0; i < size; i++) {
        num += arr[i] * pow(2, size - i - 1);
    }
    return num;
}

int main() {
    int arr1[] = {0, 0, 0, 1};
    int arr2[] = {0, 0, 1, 0};
    int arr3[] = {0, 1, 0, 1};
    int arr4[] = {1, 0, 0, 1};
    int arr5[] = {0, 0, 1, 0};
    int arr6[] = {0, 1, 1, 0};
    int arr7[] = {1, 1, 1, 1};
    int arr8[] = {1, 0, 1, 1};

    std::cout << binaryArrayToNumber(arr1, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr2, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr3, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr4, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr5, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr6, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr7, 4) << std::endl;
    std::cout << binaryArrayToNumber(arr8, 4) << std::endl;

    return 0;
}