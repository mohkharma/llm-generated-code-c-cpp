
#include <vector>

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
