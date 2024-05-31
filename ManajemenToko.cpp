#include <iostream>

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
struct transaksiToko{
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
struct PromoNode {
    string kategori;
    float diskon;
    int minBelanja;
    PromoNode* left;
    PromoNode* right;

    PromoNode(string kat, float disc, int minB) : kategori(kat), diskon(disc), minBelanja(minB), left(nullptr), right(nullptr) {}
};

//implementasi stack untuk stok barang
class stackStokBarang {
private:
    struct Node {
        inventarisToko data;
        Node* next;
    };
    Node* top;
    inventarisToko* dataBarang;
public:
    stackStokBarang() : top(nullptr) {}
    ~stackStokBarang() {
        Node* current = top;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    void push(inventarisToko data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }
    void pop() {
        if (top == nullptr) {
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }
    void display() {
        Node* current = top;
        while (current != nullptr) {
            cout << "Nama Barang: " << current->data.namaBarang << endl;
            cout << "Harga Barang: " << current->data.hargaBarang << endl;
            cout << "Stok Barang: " << current->data.stokBarang << endl;
            cout << "Kategori Barang: " << current->data.kategoriBarang << endl;
            cout << endl;
            current = current->next;
        }
    }
    void prosesStokBarang() {
        //pop semua data barang
        if (top == nullptr) {
            cout << "Tidak ada barang yang perlu diproses." << endl;
            return;
        }
        while (top != nullptr) {
            pop();
        }
    }
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
//implementasi graph untuk mencari barang yang sering dibeli
class graphBarang {
private:
    struct Node {
        string namaBarang;
        Node* next;
    };
    Node* head;
    inventarisToko* dataBarang;
public:
    graphBarang(inventarisToko* dataBarangParam) : head(nullptr), dataBarang(dataBarangParam) {}
    ~graphBarang() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    void addEdge(string namaBarang) {
        Node* newNode = new Node;
        newNode->namaBarang = namaBarang;
        newNode->next = head;
        head = newNode;
    }
    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Nama Barang: " << current->namaBarang << endl;
            current = current->next;
        }
    }
    void frequentItem() {
        //implementasi algoritma sorting - bubble sort
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            while (next != nullptr) {
                if (next->namaBarang < current->namaBarang) {
                    string temp = current->namaBarang;
                    current->namaBarang = next->namaBarang;
                    next->namaBarang = temp;
                }
                next = next->next;
            }
            current = current->next;
        }
        //implementasi algoritma searching - linear probing
        int max = 0;
        string frequentItem;
        current = head;
        while (current != nullptr) {
            int count = 0;
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->namaBarang == current->namaBarang) {
                    count++;
                }
                temp = temp->next;
            }
            if (count > max) {
                max = count;
                frequentItem = current->namaBarang;
            }
            current = current->next;
        }
        cout << "Barang yang sering dibeli: " << frequentItem << endl;
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

//implementasi tree untuk dikson dan promo
class PromoTree {
private:
    PromoNode* insert(PromoNode* node, string kat, float disc, int minB) {
        if (node == nullptr) {
            return new PromoNode(kat, disc, minB);
        }

        if (kat < node->kategori) {
            node->left = insert(node->left, kat, disc, minB);
        } else if (kat > node->kategori) {
            node->right = insert(node->right, kat, disc, minB);
        } else {
            node->diskon = disc;
            node->minBelanja = minB;
        }

        return node;
    }

    PromoNode* search(PromoNode* node, string kat) {
        //Implementasi algoritma searching - binary search
        if (node == nullptr || node->kategori == kat) {
            return node;
        }

        if (kat < node->kategori) {
            return search(node->left, kat);
        } else {
            return search(node->right, kat);
        }
    }

    void tampilkan(PromoNode* node) {
        if (node != nullptr) {
            tampilkan(node->left);
            cout << "Promo: " << node->kategori << ", " << node->diskon << "%, " << node->minBelanja << endl;
            tampilkan(node->right);
        }
    }
    PromoNode* removePromo(PromoNode* node, string kat) {
        if (node == nullptr) {
            return node;
        }

        if (kat < node->kategori) {
            node->left = removePromo(node->left, kat);
        } else if (kat > node->kategori) {
            node->right = removePromo(node->right, kat);
        } else {
            if (node->left == nullptr) {
                PromoNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                PromoNode* temp = node->left;
                delete node;
                return temp;
            }

            PromoNode* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            node->kategori = temp->kategori;
            node->diskon = temp->diskon;
            node->minBelanja = temp->minBelanja;
            node->right = removePromo(node->right, temp->kategori);
        }

        return node;
    }
    PromoNode* root;

public:
    PromoTree() : root(nullptr) {}

    void addPromo(string kat, float disc, int minB) {
        cout << "Menambahkan promo: " << kat << ", " << disc << "%, " << minB << endl;
        root = insert(root, kat, disc, minB);
    }

    void displayPromo() {
        cout << "Daftar Diskon dan Promo:" << endl;
        tampilkan(root);
    }

    PromoNode* findPromo(string kat) {
        return search(root, kat);
    }
    //buat menu hapu sdiskon permanen  dengan nama removePromo
 
    void removePromo(string kat) {
        root = removePromo(root, kat);
    }
    PromoNode* getRoot() {
        return root;
    }
    ~PromoTree() {
        delete root;
    }
};


//implementasi menu
class menuPertama {
private:
        manajemenInventarisToko inventaris;
        inventarisToko* getDataBarang() { //fungsi pointer untuk mengambil data barang
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
    PromoTree& promoTree;
    struct NodeEtalase {
        etalaseToko data;
        NodeEtalase* next;
        NodeEtalase* prev;
    };
    NodeEtalase* headEtalase;
    NodeEtalase* tailEtalase;
    inventarisToko* dataBarang;
    graphBarang graph;
    int count;

public:
    menuKedua(inventarisToko* dataBarangParam, PromoTree& promoTreeRef) : headEtalase(nullptr), tailEtalase(nullptr), dataBarang(dataBarangParam), count(0), transaksi(dataBarangParam), graph(dataBarangParam), promoTree(promoTreeRef){}

    ~menuKedua() {
        NodeEtalase* currentEtalase = headEtalase;
        while (currentEtalase != nullptr) {
            NodeEtalase* nextEtalase = currentEtalase->next;
            delete currentEtalase;
            currentEtalase = nextEtalase;
        }
    }

    // Fungsi untuk menerapkan diskon ke total harga transaksi menggunakan node dataPromo
    int diskonMasuk(int total, string kategori) {
        PromoNode* promo = promoTree.findPromo(kategori);
        if (promo != nullptr) {
            if (total >= promo->minBelanja) {
                total -= total * promo->diskon / 100;
            }
        }
        return total;
    }

    void menuLihatEtalase() {
        while (headEtalase != nullptr) {
        NodeEtalase* temp = headEtalase;
        headEtalase = headEtalase->next;
        delete temp;
        }
        tailEtalase = nullptr;
        count = 0;

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
        string kategori = item.kategoriBarang;
        total = diskonMasuk(total, kategori); // Menggunakan fungsi diskon
        string namaBarang = item.namaBarang;
        graph.addEdge(namaBarang);
        transaksiToko data = transaksiToko(idBarang, namaBarang, jumlah, total);
        transaksi.enqueue(data);
    }
    void menuLihatTransaksi() {
        transaksi.display();
    }
    void menuProsesTransaksi() {
        transaksi.prosesTransaksi();
    }
    void menuFrequentItem() {
        graph.frequentItem();
    }
};
//mengambil data barang dari menu pertama di main program
class menuTiga {
private:
    stackStokBarang stokBarang;
public:
    inventarisToko* dataBarang;
    inventarisToko* dataBarangSort;
    menuTiga(inventarisToko* dataBarangParam) : dataBarang(dataBarangParam){
    }
    ~menuTiga() {
        delete[] dataBarangSort; // Added to avoid memory leak
    }
    //dataBarangSort mencopy dataBarang jadi proses sorting tidak merubah dataBarang
    void copyDataBarang() {
        dataBarangSort = new inventarisToko[100];
        for (int i = 0; i < 100; i++) {
            dataBarangSort[i] = dataBarang[i];
        }
    }
    void menuLihatStokBarang() {
        // Implementasi algoritma sorting - bubble sort berdasarkan kategori barang dan skip jika data kosong
        copyDataBarang();
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100 - i - 1; j++) {
                if (dataBarangSort[j].kategoriBarang > dataBarangSort[j + 1].kategoriBarang) {
                    inventarisToko temp = dataBarangSort[j];
                    dataBarangSort[j] = dataBarangSort[j + 1];
                    dataBarangSort[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < 100; i++) {
            if (dataBarangSort[i].namaBarang != "") {
                cout << "Nama Barang: " << dataBarangSort[i].namaBarang << endl;
                cout << "Harga Barang: " << dataBarangSort[i].hargaBarang << endl;
                cout << "Stok Barang: " << dataBarangSort[i].stokBarang << endl;
                cout << "Kategori Barang: " << dataBarangSort[i].kategoriBarang << endl;
                cout << endl;
            }
        }
    }
    void menuTambahStokBarang() {
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
        // Push dan update stok barang di dataBarang
        inventarisToko item = dataBarang[idBarang];
        item.stokBarang += jumlah;
        dataBarang[idBarang] = item;
        stokBarang.push(item);
    }
    void menuProsesStokBarang() {
        stokBarang.prosesStokBarang();
    }
};
class menuEmpat {
private:
    inventarisToko* dataBarang;
public:
    PromoTree promoTree;
    menuEmpat(inventarisToko* dataBarangParam): dataBarang(dataBarangParam) {}

    void menuTambahDiskon() {
        string kategori;
        float diskon;
        int minBelanja;
        cin.ignore();  // Membersihkan buffer input
        cout << "Masukkan kategori barang: ";
        getline(cin, kategori);
        //mengecek apakah kategori barang ada di daftarbarang
        bool found = false;
        for (int i = 0; i < 100; i++) {
            if (dataBarang[i].kategoriBarang == kategori) {
                found = true;
                break;
            }
        }
        if (found == false) {
            cout << "Kategori barang tidak ditemukan." << endl;
            return;
        }
        cout << "Masukkan diskon (%): ";
        cin >> diskon;
        cout << "Masukkan minimal pembelian: ";
        cin >> minBelanja;
        promoTree.addPromo(kategori, diskon, minBelanja); 
    }

    void menuLihatDiskon() {
        promoTree.displayPromo();
    }

    void menuCariDiskon() {
        string kategori;
        cin.ignore();  // Membersihkan buffer input
        cout << "Masukkan kategori barang: ";
        getline(cin, kategori);
        PromoNode* promo = promoTree.findPromo(kategori);
        if (promo != nullptr) {
            cout << "Promo ditemukan: " << promo->kategori << ", " << promo->diskon << "%, " << promo->minBelanja << endl;
        } else {
            cout << "Promo untuk kategori " << kategori << " tidak ditemukan." << endl;
        }
    }
    void menuHapusDiskon() {
        string kategori;
        cin.ignore();  // Membersihkan buffer input
        cout << "Masukkan kategori barang: ";
        getline(cin, kategori);
        promoTree.removePromo(kategori);
    }
};

class mainProgram {
private:
    menuPertama inventaris;
    menuKedua transaksi;
    menuTiga stok;
    menuEmpat diskon;
    bool pendataanBarang = false;
public:
    // Constructor dan Destructor
    mainProgram() : inventaris(), transaksi(inventaris.dataBarang, diskon.promoTree),stok(inventaris.dataBarang), diskon(inventaris.dataBarang) {}
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
            cout << "| 5. Load barang Gudang  |" << endl;
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
            cout << "===============================" << endl;
            cout << "|    Program Manajemen Toko    |" << endl;
            cout << "===============================" << endl;
            cout << "| 1. Lihat Etalase             |" << endl;
            cout << "| 2. Tambah Transaksi          |" << endl;
            cout << "| 3. Lihat Transaksi           |" << endl;
            cout << "| 4. Proses Transaksi          |" << endl;
            cout << "| 5. Barang Yang Sering Dibeli |" << endl;
            cout << "| 0. Kembali                   |" << endl;
            cout << "===============================" << endl;
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
                transaksi.menuFrequentItem();
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
    void menuTiga() {
        int pilihan;
        bool isRunning = true;
        while (isRunning) {
            cout << "=========================" << endl;    
            cout << "| Program Manajemen Toko |" << endl;
            cout << "=========================" << endl;
            cout << "| 1. Lihat Stok Barang   |" << endl;
            cout << "| 2. Tambah Stok Barang  |" << endl;
            cout << "| 3. Proses Stok Barang  |" << endl;
            cout << "| 0. Kembali             |" << endl;
            cout << "=========================" << endl;
            cout << "Pilih Menu : ";
            cin >> pilihan;
            switch (pilihan) {
            case 1:
                stok.menuLihatStokBarang();
                break;
            case 2:
                stok.menuTambahStokBarang();
                break;
            case 3:
                stok.menuProsesStokBarang();
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
    void menuEmpat() {
        int pilihan;
        bool isRunning = true;
        while (isRunning) {
            cout << "=========================" << endl;    
            cout << "| Program Manajemen Toko |" << endl;
            cout << "=========================" << endl;
            cout << "| 1. Tambah Diskon       |" << endl;
            cout << "| 2. Lihat Diskon        |" << endl;
            cout << "| 3. Cari Diskon         |" << endl;
            cout << "| 4. Hapus Diskon        |" << endl;
            cout << "| 0. Kembali             |" << endl;
            cout << "=========================" << endl;
            cout << "Pilih Menu : ";
            cin >> pilihan;
            switch (pilihan) {
            case 1:
                diskon.menuTambahDiskon();
                break;
            case 2:
                diskon.menuLihatDiskon();
                break;
            case 3:
                diskon.menuCariDiskon();
                break;
            case 4:
                diskon.menuHapusDiskon();
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
    bool runProgram = true;
    while (runProgram == true)
    {
        system("cls");
        string username;
        string password;
        bool isLoggedIn = false;
        while (isLoggedIn == false)
        {
            cout << "=========================================" << endl;
            cout << "|Selamat datang di program manajemen toko|" << endl;
            cout << "=========================================" << endl;
            cout << "| 1. Login                               |" << endl;
            cout << "| 0. Keluar                              |" << endl;
            cout << "=========================================" << endl;
            cout << "Pilih Menu : ";
            int pilihan;
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                cout << "Masukkan username : ";
                cin >> username;
                cout << "Masukkan password : ";
                cin >> password;
                if (username == "admin" && password == "admin")
                {
                    isLoggedIn = true;
                }
                else if (username == "user" && password == "user")
                {
                    isLoggedIn = true;
                }
                else
                {
                    cout << "Username atau password salah" << endl;
                }
                break;
            case 0:
                runProgram = false;
                isLoggedIn = true;
                break;
            default:
                cout << "Menu tidak tersedia" << endl;
                break;
            }
        }
        if (username == "admin" && password == "admin")
        {
            int pilihan;
            bool isRunning = true;
            while (isRunning)
            {
                system("cls");
                cout << "=========================" << endl;
                cout << "| Program Manajemen Toko |" << endl;
                cout << "=========================" << endl;
                cout << "| 1. manajemen Inventaris|" << endl;
                cout << "| 2. manajemen Stok      |" << endl;
                cout << "| 3. manajemen Diskon    |" << endl;
                cout << "| 0. Logout              |" << endl;
                cout << "=========================" << endl;
                cout << "Admin Menu : ";
                cin >> pilihan;
                switch (pilihan)
                {
                    case 1:
                        program.menuPertama();
                        break;
                    case 2:
                        program.menuTiga();
                        break;
                    case 3:
                        program.menuEmpat();
                        break;
                    case 0:
                        isRunning = false;
                        break;
                }
            }
        }
        if (username == "user" && password == "user")
        {
            int pilihan;
            bool isRunning = true;
            while (isRunning)
            {
                system("cls");
                cout << "=========================" << endl;
                cout << "| Program Manajemen Toko |" << endl;
                cout << "=========================" << endl;
                cout << "| 1. manajemen Transaksi |" << endl;
                cout << "| 0. Logout              |" << endl;
                cout << "=========================" << endl;
                cout << "User Menu : ";
                cin >> pilihan;
                switch (pilihan)
                {
                    case 1:
                        program.menuKedua();
                        break;
                    case 0:
                        isRunning = false;
                        break;
                }
            }
        }
    }
    system("cls");
    cout << "+==========================================+" << endl;
    cout << "|Terima kasih telah menggunakan program ini|" << endl;
    cout << "+==========================================+" << endl;
    return 0;
}