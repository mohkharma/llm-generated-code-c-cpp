// Task176_Test.cpp

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class ProductOfNumbers {
private:
    std::vector<int> products;

public:
    ProductOfNumbers() {
        products.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            products.clear();
            products.push_back(1);
        } else {
            products.push_back(products.back() * num);
        }
    }

    int getProduct(int k) {
        int n = products.size();
        return k < n ? products.back() / products[n - k - 1] : 0;
    }
};

void runTest(const std::string& testName, int actual, int expected) {
    if (actual == expected) {
        std::cout << testName << " Passed!" << std::endl;
    } else {
        std::cout << testName << " Failed!" << std::endl;
        std::cout << "  Expected: " << expected << std::endl;
        std::cout << "  Got:      " << actual << std::endl;
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
