#include <iostream>
#include <string>

using namespace std;

class HashTable {
private:
    int size;
    int* slots;
    string* data;

public:
    HashTable(int size) {
        this->size = size;
        this->slots = new int[size];
        this->data = new string[size];
        for (int i = 0; i < size; i++) {
            slots[i] = 0; // Initialize slots to 0 (0 means empty)
            data[i] = "";
        }
    }

    ~HashTable() {
        delete[] slots;
        delete[] data;
    }

    void put(int key, string value) {
        int hashValue = hashFunction(key);

        if (slots[hashValue] == 0) {
            slots[hashValue] = key;
            data[hashValue] = value;
        } else {
            if (slots[hashValue] == key) {
                data[hashValue] = value; // replace existing
            } else {
                int nextSlot = rehash(hashValue);
                while (slots[nextSlot] != 0 && slots[nextSlot] != key) {
                    nextSlot = rehash(nextSlot);
                }

                if (slots[nextSlot] == 0) {
                    slots[nextSlot] = key;
                    data[nextSlot] = value;
                } else {
                    data[nextSlot] = value; // replace existing
                }
            }
        }
    }

    int hashFunction(int key) {
        return key % size;
    }

    int rehash(int oldHash) {
        return (oldHash + 1) % size;
    }

    string get(int key) {
        int startSlot = hashFunction(key);

        bool stop = false;
        bool found = false;
        int position = startSlot;
        string value = "";
        while (slots[position] != 0 && !found && !stop) {
            if (slots[position] == key) {
                found = true;
                value = data[position];
            } else {
                position = rehash(position);
                if (position == startSlot) {
                    stop = true;
                }
            }
        }
        return value;
    }

    void deleteKey(int key) {
        int startSlot = hashFunction(key);

        bool stop = false;
        int position = startSlot;
        while (slots[position] != 0 && !stop) {
            if (slots[position] == key) {
                slots[position] = 0;     // Mark slot as empty
                data[position] = "";     // Clear value
                return;
            } else {
                position = rehash(position);
                if (position == startSlot) {
                    stop = true;
                }
            }
        }
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
    HashTable ht(11);
    int failCount = 0;

    // Test insert and search
    ht.put(54, "cat");
    failCount += !runTest("Test Case 1", ht.get(54) == "cat");

    // Test insert overwrite
    ht.put(54, "dog");
    failCount += !runTest("Test Case 2", ht.get(54) == "dog");

    // Test search non-existent key
    failCount += !runTest("Test Case 3", ht.get(999) == "");

    // Test delete existing key
    ht.put(26, "lion");
    ht.deleteKey(26);
    failCount += !runTest("Test Case 4", ht.get(26) == "");

    // Test delete non-existent key
    ht.deleteKey(999);
    failCount += !runTest("Test Case 5", ht.get(999) == "");

    // Test insert multiple keys
    ht.put(54, "cat");
    ht.put(26, "dog");
    ht.put(93, "lion");
    failCount += !runTest("Test Case 6", ht.get(54) == "cat");
    failCount += !runTest("Test Case 7", ht.get(26) == "dog");
    failCount += !runTest("Test Case 8", ht.get(93) == "lion");

    // Test collision handling (keys 54 and 93 collide at index 10)
    ht.put(54, "cat");
    ht.put(93, "lion");
    failCount += !runTest("Test Case 9", ht.get(54) == "cat");
    failCount += !runTest("Test Case 10", ht.get(93) == "lion");

    // Test delete key from collision bucket
    ht.deleteKey(54);
    failCount += !runTest("Test Case 11", ht.get(54) == "");

    // Test insert and delete all keys
    int keys[] = {17, 77, 31, 44, 55, 20};
    string vals[] = {"tiger", "bird", "cow", "goat", "pig", "chicken"};
    for (int i = 0; i < 6; i++) {
        ht.put(keys[i], vals[i]);
    }
    for (int i = 0; i < 6; i++) {
        ht.deleteKey(keys[i]);
        failCount += !runTest("Test Case 12 for key " + to_string(keys[i]), ht.get(keys[i]) == "");
    }

    // Test reinsert after delete
    ht.put(20, "chicken");
    ht.deleteKey(20);
    ht.put(20, "duck");
    failCount += !runTest("Test Case 13", ht.get(20) == "duck");

    if (failCount == 0)
        cout << "All test cases passed!\n";
    else
        cout << failCount << " test(s) failed.\n";

    return failCount;
}
