#include <iostream>

int main() {
    // Dynamically allocate memory
    int* myArray = new int[10];

    // Use the array...

    // Deallocate memory
    delete[] myArray;

    return 0;
}