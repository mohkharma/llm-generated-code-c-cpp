
#include <iostream>
#include <string>
#include <algorithm>

long long largestSeriesProduct(const std::string& inputSequence, int span) {
    if (span > inputSequence.length() || span <= 0) {
        return -1; // Invalid input
    }
    
    long long maxProduct = 0;
    
    for (int i = 0; i <= inputSequence.length() - span; ++i) {
        long long product = 1;
        for (int j = i; j < i + span; ++j) {
            product *= inputSequence[j] - '0';
        }
        maxProduct = std::max(maxProduct, product);
    }
    
    return maxProduct;
}
