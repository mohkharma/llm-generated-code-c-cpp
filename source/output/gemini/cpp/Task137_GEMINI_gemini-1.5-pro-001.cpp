#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct Product {
    string name;
    double price;
    int stock;
};

unordered_map<string, Product> products = {
    {"001", {"Apple", 1.00, 100}},
    {"002", {"Banana", 0.50, 50}},
    {"003", {"Orange", 1.20, 75}}
};

string getProductDetails(const string& productId) {
    auto product = products.find(productId);
    if (product != products.end()) {
        return "Product Name: " + product->second.name + "\nPrice: $" + to_string(product->second.price) + "\nStock: " + to_string(product->second.stock);
    } else {
        return "Product not found.";
    }
}

int main() {
    string productId;

    while (true) {
        cout << "Enter product ID (or 'q' to quit): ";
        cin >> productId;
        if (productId == "q") {
            break;
        }
        cout << getProductDetails(productId) << endl;
    }

    return 0;
}
