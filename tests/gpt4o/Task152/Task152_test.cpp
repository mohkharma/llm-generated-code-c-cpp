#include <iostream>
#include <list>
#include <vector>
#include <string>

class HashTable {
private:
    const int SIZE = 10;
    std::vector<std::list<std::pair<int, std::string>>> table;

    int hashFunction(int key) const {
        return key % SIZE;
    }

public:
    HashTable() : table(SIZE) {}

    void insert(int key, const std::string& value) {
        int hashKey = hashFunction(key);
        // تحديث إذا المفتاح موجود
        for (auto& entry : table[hashKey]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[hashKey].emplace_back(key, value);
    }

    void deleteKey(int key) {
        int hashKey = hashFunction(key);
        auto& bucket = table[hashKey];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                break;
            }
        }
    }

    std::string search(int key) const {
        int hashKey = hashFunction(key);
        for (const auto& entry : table[hashKey]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return "";
    }
};

bool runTest(const std::string& testName, bool condition) {
    if (!condition) {
        std::cerr << testName << " Failed\n";
        return false;
    }
    return true;
}

int main() {
    int failCount = 0;
    HashTable ht;

    // Test insert and search
    ht.insert(1, "one");
    failCount += !runTest("Test Case 1", ht.search(1) == "one");

    // Test insert overwrite
    ht.insert(1, "uno");
    failCount += !runTest("Test Case 2", ht.search(1) == "uno");

    // Test search non-existent key
    failCount += !runTest("Test Case 3", ht.search(999) == "");

    // Test delete existing key
    ht.insert(1, "one");
    ht.deleteKey(1);
    failCount += !runTest("Test Case 4", ht.search(1) == "");

    // Test delete non-existent key
    ht.deleteKey(999);
    failCount += !runTest("Test Case 5", ht.search(999) == "");

    // Test insert multiple keys (including collision keys 1 and 11)
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(11, "eleven");
    failCount += !runTest("Test Case 6", ht.search(1) == "one");
    failCount += !runTest("Test Case 7", ht.search(2) == "two");
    failCount += !runTest("Test Case 8", ht.search(11) == "eleven");

    // Test collision keys separately
    ht.insert(1, "one-again");
    failCount += !runTest("Test Case 9", ht.search(1) == "one-again");
    failCount += !runTest("Test Case 10", ht.search(11) == "eleven");

    // Test delete key after collision
    ht.deleteKey(1);
    failCount += !runTest("Test Case 11", ht.search(1) == "");

    // Test insert and delete all keys
    int keys[] = {3, 4, 5};
    for (int k : keys) {
        ht.insert(k, "val" + std::to_string(k));
    }
    for (int k : keys) {
        ht.deleteKey(k);
        failCount += !runTest("Test Case 12 for key " + std::to_string(k), ht.search(k) == "");
    }

    // Test reinsert after delete
    ht.insert(100, "hundred");
    ht.deleteKey(100);
    ht.insert(100, "hundred-again");
    failCount += !runTest("Test Case 13", ht.search(100) == "hundred-again");

    if (failCount == 0)
        std::cout << "All test cases passed!\n";
    else
        std::cout << failCount << " test(s) failed.\n";

    return failCount;
}
