class HashTable {
public:  // <--- هنا
    static const int SIZE = 10000;
private:
    std::vector<std::list<std::pair<int, int>>> table;

    int hash(int key) const {
        return std::abs(key) % SIZE;
    }

public:
    HashTable() : table(SIZE) {}

    void insert(int key, int value) {
        for (auto& entry : table[hash(key)]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[hash(key)].emplace_back(key, value);
    }

    void deleteKey(int key) {
        auto& bucket = table[hash(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                break;
            }
        }
    }

    int search(int key) {
        auto& bucket = table[hash(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return -1;
    }
};
