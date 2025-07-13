// Task176_Test.cpp

#include <iostream>
#include <vector>

// =====================
// الكود الأصلي كما هو
// =====================
class ProductOfNumbers {
public:
    std::vector<int> prefixProducts;

    ProductOfNumbers() {
        prefixProducts.push_back(1); // Initialize with 1 for empty subarrays
    }

    void add(int num) {
        if (num == 0) {
            prefixProducts.clear(); // Reset prefix products when encountering 0
            prefixProducts.push_back(1);
        } else {
            prefixProducts.push_back(prefixProducts.back() * num);
        }
    }

    int getProduct(int k) {
        int n = prefixProducts.size();
        if (k >= n) {
            return 0; // Not enough elements for the product
        }
        return prefixProducts.back() / prefixProducts[n - k - 1];
    }
};


void runTest(const std::string& testName, int actual, int expected) {
    if (actual == expected) {
        std::cout << testName << " Passed!\n";
    } else {
        std::cout << testName << " Failed!\n";
        std::cout << "  Expected: " << expected << "\n";
        std::cout << "  Got:      " << actual << "\n";
    }
}


int main() {
    ProductOfNumbers productOfNumbers;

    productOfNumbers.add(3);
    productOfNumbers.add(0);
    productOfNumbers.add(2);
    productOfNumbers.add(5);
    productOfNumbers.add(4);
    runTest("Test Case 1", productOfNumbers.getProduct(2), 20);
    runTest("Test Case 2", productOfNumbers.getProduct(3), 40);
    runTest("Test Case 3", productOfNumbers.getProduct(4), 0);

    productOfNumbers.add(8);
    runTest("Test Case 4", productOfNumbers.getProduct(2), 32);

    productOfNumbers.add(6);
    runTest("Test Case 5", productOfNumbers.getProduct(3), 192);

    productOfNumbers = ProductOfNumbers();
    productOfNumbers.add(5);
    runTest("Test Case 6", productOfNumbers.getProduct(1), 5);

    productOfNumbers.add(0);
    runTest("Test Case 7", productOfNumbers.getProduct(1), 0);

    productOfNumbers.add(1);
    productOfNumbers.add(2);
    productOfNumbers.add(3);
    productOfNumbers.add(4);
    runTest("Test Case 8", productOfNumbers.getProduct(4), 24);

    productOfNumbers = ProductOfNumbers();
    productOfNumbers.add(1);
    productOfNumbers.add(2);
    productOfNumbers.add(3);
    productOfNumbers.add(4);
    productOfNumbers.add(5);
    runTest("Test Case 9", productOfNumbers.getProduct(3), 60);

    productOfNumbers.add(0);
    runTest("Test Case 10", productOfNumbers.getProduct(2), 0);

    return 0;
}
