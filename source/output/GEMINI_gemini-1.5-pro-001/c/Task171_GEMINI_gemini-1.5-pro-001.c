int mergeAndCount(int *left, int n1, int *right, int n2, int *merged) {
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    while (i < n1 && j < n2) {
        if (left[i] > 2 * right[j]) {
            count += n1 - i;
            j++;
        } else {
            i++;
        }
    }
    while (i < n1) {
        merged[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        merged[k] = right[j];
        j++;
        k++;
    }
    return count;
}

int reversePairs(int *nums, int n) {
    if (n <= 1) {
        return 0;
    }
    int mid = n / 2;
    int *left = (int *)malloc(sizeof(int) * mid);
    int *right = (int *)malloc(sizeof(int) * (n - mid));
    for (int i = 0; i < mid; i++) {
        left[i] = nums[i];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid] = nums[i];
    }
    int count = reversePairs(left, mid) + reversePairs(right, n - mid);
    int *merged = (int *)malloc(sizeof(int) * n);
    count += mergeAndCount(left, mid, right, n - mid, merged);
    for (int i = 0; i < n; i++) {
        nums[i] = merged[i];
    }
    free(left);
    free(right);
    free(merged);
    return count;
}