#include <iostream>

class HashTable {
private:
    std::pair<int, int>** table;
    int size;

public:
    HashTable(int size) {
        this->size = size;
        table = new std::pair<int, int>*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            delete table[i];
        }
        delete[] table;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        if (table[index] == nullptr) {
            table[index] = new std::pair<int, int>(key, value);
        } else {
            std::pair<int, int>* current = table[index];
            while (current->second != -1 && current->first != key) {
                index = (index + 1) % size;
                current = table[index];
            }
            delete table[index];
            table[index] = new std::pair<int, int>(key, value);
        }
    }

    int search(int key) {
        int index = hashFunction(key);
        std::pair<int, int>* current = table[index];
        while (current != nullptr) {
            if (current->first == key) {
                return current->second;
            }
            index = (index + 1) % size;
            current = table[index];
        }
        return -1; // Key not found
    }

    void remove(int key) {
        int index = hashFunction(key);
        std::pair<int, int>* current = table[index];
        while (current != nullptr) {
            if (current->first == key) {
                delete table[index];
                table[index] = nullptr;
                break;
            }
            index = (index + 1) % size;
            current = table[index];
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