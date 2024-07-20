int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long sums[numsSize + 1];
    memset(sums, 0, sizeof(sums));
    for (int i = 0; i < numsSize; i++) {
        sums[i + 1] = sums[i] + nums[i];
    }
    
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j <= numsSize; j++) {
            if (lower <= sums[j] - sums[i] && sums[j] - sums[i] <= upper) {
                count++;
            }
        }
    }
    
    return count;
}