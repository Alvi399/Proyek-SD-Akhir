#include <iostream>
#include <string>

using namespace std;

struct inventarisToko { //implementasi struct
    string namaBarang;
    int hargaBarang;
    int stokBarang;
    string kategoriBarang;
    inventarisToko() : namaBarang(""), hargaBarang(0), stokBarang(0), kategoriBarang("") {}
    inventarisToko(string nama, int harga, int stok, string kategori)
        : namaBarang(nama), hargaBarang(harga), stokBarang(stok), kategoriBarang(kategori) {}
};
struct transaksiToko
{
    int idTransaksi;
    string namaBarang;
    int jumlahBarang;
    int totalHarga;
    transaksiToko() : idTransaksi(0), jumlahBarang(0), totalHarga(0) {}
    transaksiToko(int id, string nama, int jumlah, int total)
        : idTransaksi(id), jumlahBarang(jumlah), totalHarga(total),namaBarang(nama) {}
};
struct etalaseToko
{
    int idBarang;
    string namaBarang;
    int hargaBarang;
    int stokBarang;
    string kategoriBarang;
    etalaseToko() : idBarang(0),namaBarang(""), hargaBarang(0), stokBarang(0), kategoriBarang("") {}
    etalaseToko(int id, string nama, int harga, int stok, string kategori)
        : idBarang(id),namaBarang(nama), hargaBarang(harga), stokBarang(stok), kategoriBarang(kategori) {}
};
//implementasi queue untuk transaksi
class queueTransaksi {
private:
    struct Node {
        transaksiToko data;
        Node* next;
    };
    Node* head;
    Node* tail;
    inventarisToko* dataBarang;

public:
    queueTransaksi(inventarisToko* dataBarangParam) : head(nullptr), tail(nullptr), dataBarang(dataBarangParam) {}
    ~queueTransaksi() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void enqueue(transaksiToko data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void dequeue() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Nama Barang: " << current->data.namaBarang << endl;
            cout << "Jumlah Barang: " << current->data.jumlahBarang << endl;
            cout << "Total Harga: " << current->data.totalHarga << endl;
            cout << endl;
            current = current->next;
        }
    }

void prosesTransaksi() {
    if (head == nullptr) {
        cout << "Tidak ada transaksi yang perlu diproses." << endl;
        return;
    }

    int total = 0;
    Node* current = head;
    
    // Hitung total semua transaksi
    while (current != nullptr) {
        cout << "Nama Barang: " << current->data.namaBarang << endl;
        cout << "Jumlah Barang: " << current->data.jumlahBarang << endl;
        cout << "Total Harga: " << current->data.totalHarga << endl;
        cout << endl;
        total += current->data.totalHarga;
        current = current->next;
    }

    int uang;
    cout << "Total belanja: " << total << endl;
    cout << "Masukkan uang pelanggan: ";
    cin >> uang;
    cout << "Uang pelanggan: " << uang << endl;
    cout << "Kembalian: " << uang - total << endl;
    cout << "Transaksi berhasil!" << endl;

    // Hapus semua transaksi dan kurangi stok barang
    while (head != nullptr) {
        inventarisToko* item = &dataBarang[head->data.idTransaksi];
        item->stokBarang -= head->data.jumlahBarang;
        dequeue();
    }
}
};
class manajemenInventarisToko { 
private:
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
    inventarisToko* table;
    manajemenInventarisToko(int size) {
        this->size = size;
        this->count = 0;
        table = new inventarisToko[size];
    }
    ~manajemenInventarisToko() {
        delete[] table;
    }
    void insert(string key, inventarisToko value) { //implementasi hashing - linear probing
        int index = hashFunction(key);
        //implementasion colosion handling 
        while (table[index].namaBarang != "" && table[index].namaBarang != key) {
            index = (index + 1) % size;
        }
        if (table[index].namaBarang == "") {
            count++;
        }
        table[index] = value;
    }
    inventarisToko search(string key) { //implementasi algorima searching - linear probing
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


//implementasi menu
class menuPertama {
private:
        manajemenInventarisToko inventaris;
        inventarisToko* getDataBarang() {
            return inventaris.table;
        }
    public:
        // Constructor dan Destructor
        menuPertama() : inventaris(100) {}
        ~menuPertama() {}

    //fungsi untuk menejemen inventaris
    inventarisToko* dataBarang = getDataBarang();
    void menuTambahBarang() {
        string nama;
        int harga, stok;
        string kategori;
        cin.ignore();
        cout << "Masukkan nama barang: ";
        cin >> nama;
        cin.ignore();
        cout << "Masukkan harga barang: ";
        cin >> harga;
        cin.ignore();
        cout << "Masukkan stok barang: ";
        cin >> stok;
        cin.ignore();
        cout << "Masukkan kategori barang: ";
        cin >> kategori;
        inventaris.insert(nama, inventarisToko(nama, harga, stok, kategori));
    }
    void menuHapusBarang() {
        string nama;
        cin.ignore();
        cout << "Masukkan nama barang yang ingin dihapus: ";
        cin >> nama;
        inventaris.remove(nama);
    }
    void menuCariBarang() {
        string nama;
        cin.ignore();
        cout << "Masukkan nama barang yang ingin dicari: ";
        cin >> nama;
        inventarisToko result = inventaris.search(nama);
        if (result.namaBarang != "") {
            cout << "Barang ditemukan: " << result.namaBarang << " " << result.hargaBarang << " " << result.stokBarang << " " << result.kategoriBarang << endl;
        } else {
            cout << "Barang tidak ditemukan" << endl;
        }
    }
    void menuLoadBarang() {
        //insert barang barang pokok
        inventaris.insert("Beras", inventarisToko("Beras", 10000, 100, "Makanan"));
        inventaris.insert("Gula", inventarisToko("Gula", 15000, 50, "Makanan"));
        inventaris.insert("Minyak",inventarisToko("Minyak", 20000, 30, "Makanan"));
        inventaris.insert("Sabun", inventarisToko("Sabun", 5000, 200, "Peralatan Mandi"));
        inventaris.insert("Shampoo", inventarisToko("Shampoo", 10000, 100, "Peralatan Mandi"));
        inventaris.insert("Pasta Gigi", inventarisToko("Pasta Gigi",5000, 100, "Peralatan Mandi"));
    }
    void menuTampilkanBarang() {
        inventaris.display();
    }
};
class menuKedua {
private:
    queueTransaksi transaksi;
    struct NodeEtalase {
        etalaseToko data;
        NodeEtalase* next;
        NodeEtalase* prev;
    };
    NodeEtalase* headEtalase;
    NodeEtalase* tailEtalase;
    inventarisToko* dataBarang;
    int count;

public:
    menuKedua(inventarisToko* dataBarangParam) : headEtalase(nullptr), tailEtalase(nullptr), dataBarang(dataBarangParam), count(0), transaksi(dataBarangParam) {}
    ~menuKedua() {
        NodeEtalase* currentEtalase = headEtalase;
        while (currentEtalase != nullptr) {
            NodeEtalase* nextEtalase = currentEtalase->next;
            delete currentEtalase;
            currentEtalase = nextEtalase;
        }
    }

    void menuLihatEtalase() {
        if (headEtalase == nullptr) {
            for (int i = 0; i < 100; i++) {
                if (dataBarang[i].namaBarang != "") {
                    NodeEtalase* newNode = new NodeEtalase;
                    newNode->data.idBarang = i;
                    newNode->data.namaBarang = dataBarang[i].namaBarang;
                    newNode->data.hargaBarang = dataBarang[i].hargaBarang;
                    newNode->data.stokBarang = dataBarang[i].stokBarang;
                    newNode->data.kategoriBarang = dataBarang[i].kategoriBarang;
                    newNode->next = nullptr;
                    newNode->prev = tailEtalase;
                    if (headEtalase == nullptr) {
                        headEtalase = newNode;
                        tailEtalase = newNode;
                    } else {
                        tailEtalase->next = newNode;
                        tailEtalase = newNode;
                    }
                    count++;
                }
            }
        }

        NodeEtalase* current = headEtalase;
        char command;
        while (current != nullptr) {
            cout << "ID Barang: " << current->data.idBarang << endl;
            cout << "Nama Barang: " << current->data.namaBarang << endl;
            cout << "Harga Barang: " << current->data.hargaBarang << endl;
            cout << "Stok Barang: " << current->data.stokBarang << endl;
            cout << "Kategori Barang: " << current->data.kategoriBarang << endl;
            cout << endl;
            cout << "Tekan 'n' untuk next, 'p' untuk previous, 'q' untuk keluar: ";
            cin >> command;
            if (command == 'n' && current->next != nullptr) {
                current = current->next;
            } else if (command == 'p' && current->prev != nullptr) {
                current = current->prev;
            } else if (command == 'q') {
                break;
            } else {
                cout << "Perintah tidak valid atau tidak ada data lagi." << endl;
            }
        }
    }

    void menuTambahTransaksi() {
        int idBarang;
        int jumlah;
        cout << "Masukkan id barang: ";
        cin >> idBarang;
        cout << "Masukkan jumlah barang: ";
        cin >> jumlah;

        if (idBarang < 0 || idBarang >= 100 || dataBarang[idBarang].namaBarang == "") {
            cout << "ID barang tidak valid!" << endl;
            return;
        }

        if (jumlah <= 0) {
            cout << "Jumlah barang tidak valid!" << endl;
            return;
        }

        inventarisToko item = dataBarang[idBarang];
        //debug
        cout << "Nama Barang: " << item.namaBarang << endl;
        cout << "Harga Barang: " << item.hargaBarang << endl;
        cout << "Stok Barang: " << item.stokBarang << endl;
        cout << "Kategori Barang: " << item.kategoriBarang << endl;
    
        int total = item.hargaBarang * jumlah;
        string namaBarang = item.namaBarang;
        transaksiToko data = transaksiToko(idBarang, namaBarang, jumlah, total);
        transaksi.enqueue(data);
    }

    void menuLihatTransaksi() {
        transaksi.display();
    }

    void menuProsesTransaksi() {
        transaksi.prosesTransaksi();
    }
    void menudebug() {
        transaksi.dequeue();
    }
};


class mainProgram {
private:
    menuPertama inventaris;
    menuKedua transaksi;
    bool pendataanBarang = false;
    inventarisToko* dataBarang = inventaris.dataBarang;
public:
    // Constructor dan Destructor
    mainProgram() : inventaris(), transaksi(inventaris.dataBarang) {}
    ~mainProgram() {}
    void menuPertama() {
        int pilihan;
        bool isRunning = true;
        while (isRunning) {
            cout << "=========================" << endl;
            cout << "| Program Manajemen Toko |" << endl;
            cout << "=========================" << endl;
            cout << "| 1. Tambah Barang       |" << endl;
            cout << "| 2. Hapus Barang        |" << endl;
            cout << "| 3. Cari Barang         |" << endl;
            cout << "| 4. Tampilkan Barang    |" << endl;
            cout << "| 5. Load barang kudang  |" << endl;
            cout << "| 0. Kembali             |" << endl;
            cout << "=========================" << endl;
            cout << "Pilih Menu : ";
            cin >> pilihan;
            switch (pilihan) {
            case 1:
                inventaris.menuTambahBarang();
                break;
            case 2:
                inventaris.menuHapusBarang();
                break;
            case 3:
                inventaris.menuCariBarang();
                break;
            case 4:
                inventaris.menuTampilkanBarang();
                break;
            case 5:
                if (pendataanBarang == false)
                {
                    inventaris.menuLoadBarang();
                    pendataanBarang = true;
                }
                else if (pendataanBarang == true)
                {
                    cout << "Data barang sudah di load" << endl;
                }
                else
                {
                    cout << "Data barang tidak ada" << endl;
                }
                
            case 0:
                isRunning = false;
                break;
            default:
                cout << "Menu tidak tersedia" << endl;
                break;
            }
        }
    }
    void menuKedua() {
        int pilihan;
        bool isRunning = true;
        while (isRunning) {
            cout << "=========================" << endl;
            cout << "| Program Manajemen Toko |" << endl;
            cout << "=========================" << endl;
            cout << "| 1. Lihat Etalase       |" << endl;
            cout << "| 2. Tambah Transaksi     |" << endl;
            cout << "| 3. Lihat Transaksi      |" << endl;
            cout << "| 4. Proses Transaksi     |" << endl;
            cout << "| 0. Kembali              |" << endl;
            cout << "| 5. debug                |" << endl;
            cout << "=========================" << endl;
            cout << "Pilih Menu : ";
            cin >> pilihan;
            switch (pilihan) {
            case 1:
                transaksi.menuLihatEtalase();
                break;
            case 2:
                transaksi.menuTambahTransaksi();
                break;
            case 3:
                transaksi.menuLihatTransaksi();
                break;
            case 4:
                transaksi.menuProsesTransaksi();
                break;
            case 5:
                transaksi.menudebug();
                break;
            case 0:
                isRunning = false;
                break;
            default:
                cout << "Menu tidak tersedia" << endl;
                break;
            }
        }
    }    
};

int main() {
    mainProgram program;
    bool isRunning = true;

    while (isRunning)
    {
        int pilihan;
        system("cls");
        cout << "=========================" << endl;
        cout << "| Program Manajemen Toko |" << endl;
        cout << "=========================" << endl;
        cout << "| 1. manajemen Inventaris|" << endl;
        cout << "| 2. manajemen Transaksi |" << endl;
        cout << "| 3. Exit                |" << endl;
        cout << "=========================" << endl;
        cout << "Pilih Menu : ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                program.menuPertama();
                break;
            case 2:
                program.menuKedua();
                break;
            case 3:
                isRunning = false;
                break;
            default:
                cout << "Menu tidak tersedia" << endl;
                break;
        }
    }
    
}
