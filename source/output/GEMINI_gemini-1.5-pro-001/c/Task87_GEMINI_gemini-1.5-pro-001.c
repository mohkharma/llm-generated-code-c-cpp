#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int array[], int x, int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (array[mid] == x)
      return mid;

    if (array[mid] < x)
      low = mid + 1;

    else
      high = mid - 1;
  }

  return -1;
}

int main(void) {
  int n;
  printf("Enter the number of elements: ");
  scanf("%d", &n);
  int array[n];
  printf("Enter %d integers:
", n);
  for (int i = 0; i < n; i++)
    scanf("%d", &array[i]);

  int x;
  printf("Enter element to search: ");
  scanf("%d", &x);
  clock_t begin = clock();
  int result = binarySearch(array, x, 0, n - 1);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  FILE *fptr;
  fptr = fopen("search_time.txt", "w");

  if(result == -1)
    printf("Not found");
  else
    printf("Element is found at index %d", result);
  fprintf(fptr, "Time taken: %f seconds
", time_spent);
  fclose(fptr);
  return 0;
}