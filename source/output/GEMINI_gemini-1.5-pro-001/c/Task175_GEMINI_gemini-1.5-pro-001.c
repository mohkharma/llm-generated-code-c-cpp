#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
} MountainArray;

int get(MountainArray *obj, int index) {
    return obj->array[index];
}

int length(MountainArray *obj) {
    return obj->size;
}
int binarySearch(MountainArray *mountainArr, int target, int left, int right, int ascending) {
    while (left <= right) {
        int mid = (left + right) / 2;
        int midVal = get(mountainArr, mid);
        if (midVal == target) {
            return mid;
        } else if ((midVal < target && ascending) || (midVal > target && !ascending)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
int findInMountainArray(int target, MountainArray *mountainArr) {
    int n = length(mountainArr);
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (get(mountainArr, mid) < get(mountainArr, mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int peak = left;
    int index = binarySearch(mountainArr, target, 0, peak, 1);
    if (index != -1) {
        return index;
    }
    return binarySearch(mountainArr, target, peak + 1, n - 1, 0);
}
int main() {
    int arr[] = {1, 2, 3, 4, 5, 3, 1};
    MountainArray mountainArr = {arr, sizeof(arr) / sizeof(arr[0])};
    int target = 3;
    int result = findInMountainArray(target, &mountainArr);
    // Output: 2
    return 0;
}