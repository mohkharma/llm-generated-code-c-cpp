#include <iostream>
#include <string>

int largestProduct(const std::string& inputStr, int span) {
    int maxProduct = 0;
    for (int i = 0; i <= inputStr.length() - span; i++) {
        int product = 1;
        for (int j = 0; j < span; j++) {
            product *= inputStr[i + j] - '0';
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

