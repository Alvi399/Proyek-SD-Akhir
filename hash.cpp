#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<std::vector<std::pair<int, int>>> table;
    int size;

public:
    HashTable(int size) {
        this->size = size;
        table.resize(size);
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        table[index].push_back(std::make_pair(key, value));
    }

    int search(int key) {
        int index = hashFunction(key);
        for (auto pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1; // Key not found
    }

    void remove(int key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                break;
            }
        }
    }
};

int main() {
    HashTable hashTable(10);

    hashTable.insert(1, 10);
    hashTable.insert(2, 20);
    hashTable.insert(11, 30);

    std::cout << hashTable.search(1) << std::endl; // Output: 10
    std::cout << hashTable.search(2) << std::endl; // Output: 20
    std::cout << hashTable.search(11) << std::endl; // Output: 30
    std::cout << hashTable.search(3) << std::endl; // Output: -1 (Key not found)

    hashTable.remove(2);

    std::cout << hashTable.search(2) << std::endl; // Output: -1 (Key not found)

    return 0;
}