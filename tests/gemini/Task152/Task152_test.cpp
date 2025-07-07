#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    int size;
    vector<list<pair<K, V>>> table;

    int _hash(const K& key) const {
        return hash<K>{}(key) % size;
    }

public:
    HashTable(int size) : size(size), table(size) {}

    void insert(const K& key, const V& value) {
        int index = _hash(key);
        // Update if key exists
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].push_back(make_pair(key, value));
    }

    bool deleteItem(const K& key) {
        int index = _hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    V* search(const K& key) {
        int index = _hash(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const HashTable<K, V>& ht) {
        for (int i = 0; i < ht.size; ++i) {
            os << "Index " << i << ": ";
            for (const auto& entry : ht.table[i]) {
                os << "(" << entry.first << ", " << entry.second << ") ";
            }
            os << endl;
        }
        return os;
    }
};

bool runTest(const string& testName, bool condition) {
    if (!condition) {
        cerr << testName << " Failed\n";
        return false;
    }
    return true;
}

int main() {
    int failCount = 0;
    HashTable<int, int> table(10000);

    // Test insert and search
    table.insert(1, 100);
    failCount += !runTest("Test Case 1", table.search(1) && *table.search(1) == 100);

    // Test insert overwrite
    table.insert(1, 200);
    failCount += !runTest("Test Case 2", table.search(1) && *table.search(1) == 200);

    // Test search non-existent key
    failCount += !runTest("Test Case 3", table.search(99999) == nullptr);

    // Test delete existing key
    table.insert(1, 100);
    table.deleteItem(1);
    failCount += !runTest("Test Case 4", table.search(1) == nullptr);

    // Test delete non-existent key
    table.deleteItem(99999);
    failCount += !runTest("Test Case 5", table.search(99999) == nullptr);

    // Test insert multiple keys
    table.insert(1, 100);
    table.insert(2, 200);
    table.insert(3, 300);
    failCount += !runTest("Test Case 6", table.search(1) && *table.search(1) == 100);
    failCount += !runTest("Test Case 7", table.search(2) && *table.search(2) == 200);
    failCount += !runTest("Test Case 8", table.search(3) && *table.search(3) == 300);

    // Test collision handling (force collision)
    int keyA = 5;
    int keyB = 5 + 10000; // same bucket due to mod by size
    table.insert(keyA, 555);
    table.insert(keyB, 999);
    failCount += !runTest("Test Case 9", table.search(keyA) && *table.search(keyA) == 555);
    failCount += !runTest("Test Case 10", table.search(keyB) && *table.search(keyB) == 999);

    // Test delete key from bucket after collision insert
    table.deleteItem(keyA);
    failCount += !runTest("Test Case 11", table.search(keyA) == nullptr);

    // Test insert and delete all keys
    int keys[] = {10, 20, 30, 40, 50};
    for (int k : keys) {
        table.insert(k, k * 10);
    }
    for (int k : keys) {
        table.deleteItem(k);
        failCount += !runTest("Test Case 12 for key " + to_string(k), table.search(k) == nullptr);
    }

    // Test reinsert after delete
    table.insert(100, 1234);
    table.deleteItem(100);
    table.insert(100, 4321);
    failCount += !runTest("Test Case 13", table.search(100) && *table.search(100) == 4321);

    if (failCount == 0)
        cout << "All test cases passed!\n";
    else
        cout << failCount << " test(s) failed.\n";

    return failCount;
}
