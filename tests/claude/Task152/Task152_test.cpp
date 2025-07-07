#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>

template<typename K, typename V>
class HashTable {
private:
    static const int SIZE = 10;
    std::vector<std::list<std::pair<K, V>>> table;

    int hashFunction(const K& key) const {
        return std::hash<K>{}(key) % SIZE;
    }

public:
    HashTable() : table(SIZE) {}

    void insert(const K& key, const V& value) {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    void remove(const K& key) {
        int index = hashFunction(key);
        table[index].remove_if([&key](const auto& entry) { return entry.first == key; });
    }

    V* search(const K& key) {
        int index = hashFunction(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }
};

int main() {
    int failCount = 0;
    HashTable<std::string, std::string> table;

    table.insert("key1", "value1");
    failCount += !(table.search("key1") && *table.search("key1") == "value1");

    table.insert("key1", "value2");
    failCount += !(table.search("key1") && *table.search("key1") == "value2");

    failCount += !(table.search("nonexistent_key") == nullptr);

    table.insert("key1", "value1");
    table.remove("key1");
    failCount += !(table.search("key1") == nullptr);

    table.remove("nonexistent_key");
    failCount += !(table.search("nonexistent_key") == nullptr);

    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("key3", "value3");
    failCount += !(table.search("key1") && *table.search("key1") == "value1");
    failCount += !(table.search("key2") && *table.search("key2") == "value2");
    failCount += !(table.search("key3") && *table.search("key3") == "value3");

    table.remove("key1");
    failCount += !(table.search("key1") == nullptr);

    std::string keys[] = {"key1","key2","key3","key4","key5"};
    for (auto& k : keys) {
        table.insert(k, "value_" + k);
    }
    for (auto& k : keys) {
        table.remove(k);
        failCount += !(table.search(k) == nullptr);
    }

    table.insert("key1", "value1");
    table.remove("key1");
    table.insert("key1", "value2");
    failCount += !(table.search("key1") && *table.search("key1") == "value2");

    if (failCount == 0)
        std::cout << "All test cases passed!\n";
    else
        std::cout << failCount << " test(s) failed.\n";

    return failCount;
}
