#include <iostream>
#include <string>

using namespace std;

struct inventarisToko {
    string namaBarang;
    int hargaBarang;
    int stokBarang;
    string kategoriBarang;

    inventarisToko() : namaBarang(""), hargaBarang(0), stokBarang(0), kategoriBarang("") {}
    inventarisToko(string nama, int harga, int stok, string kategori)
        : namaBarang(nama), hargaBarang(harga), stokBarang(stok), kategoriBarang(kategori) {}
};

class manajemenInventarisToko {
private:
    inventarisToko* table;
    int size;
    int count;
    int hashFunction(string key) {
        int sum = 0;
        for (char ch : key) {
            sum += ch;
        }
        return sum % size;
    }
public:
    manajemenInventarisToko(int size) {
        this->size = size;
        this->count = 0;
        table = new inventarisToko[size];
    }
    ~manajemenInventarisToko() {
        delete[] table;
    }
    void insert(string key, inventarisToko value) {
        int index = hashFunction(key);
        // Linear probing
        while (table[index].namaBarang != "" && table[index].namaBarang != key) {
            index = (index + 1) % size;
        }
        if (table[index].namaBarang == "") {
            count++;
        }
        table[index] = value;
    }
    inventarisToko search(string key) {
        int index = hashFunction(key);
        // Linear probing
        while (table[index].namaBarang != "" && table[index].namaBarang != key) {
            index = (index + 1) % size;
        }
        if (table[index].namaBarang == key) {
            return table[index];
        } else {
            return inventarisToko();  // Key not found, return default object
        }
    }
    void remove(string key) {
        int index = hashFunction(key);
        // Linear probing
        while (table[index].namaBarang != "" && table[index].namaBarang != key) {
            index = (index + 1) % size;
        }
        if (table[index].namaBarang == key) {
            table[index] = inventarisToko();  // Set to default object
            count--;
        }
    }
    void display() {
        for (int i = 0; i < size; i++) {
            if (table[i].namaBarang != "") {
                cout << "Bucket " << i << ": (" << table[i].namaBarang << ", " << table[i].hargaBarang << ", "
                    << table[i].stokBarang << ", " << table[i].kategoriBarang << ") -> ";
            } else {
                cout << "Bucket " << i << ": None";
            }
            cout << endl;
        }
    }
};

int main() {
    manajemenInventarisToko inventory(10);

    inventory.insert("Keyboard", inventarisToko("Keyboard", 150000, 10, "Elektronik"));
    inventory.insert("Mouse", inventarisToko("Mouse", 50000, 25, "Elektronik"));
    inventory.insert("Monitor", inventarisToko("Monitor", 2000000, 5, "Elektronik"));
    inventory.insert("Printer", inventarisToko("Printer", 1200000, 7, "Elektronik"));

    inventory.display();

    cout << "Search for 'Mouse': ";
    inventarisToko item = inventory.search("Mouse");
    if (item.namaBarang != "") {
        cout << item.namaBarang << " ditemukan dengan harga " << item.hargaBarang << endl;
    } else {
        cout << "Tidak ditemukan" << endl;
    }

    inventory.remove("Mouse");
    cout << "Setelah menghapus 'Mouse':" << endl;
    inventory.display();

    return 0;
}
