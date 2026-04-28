#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Toko Sembako
struct BarangNode {
    string namaBarang;
    int stok;
    BarangNode* next;

    // Constructor
    BarangNode(string nama, int jumlah) {
        namaBarang = nama;
        stok = jumlah;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List untuk membangun data
BarangNode* tambahBarang(BarangNode* head, string nama, int jumlah) {
    BarangNode* newNode = new BarangNode(nama, jumlah);

    // Jika linked list masih kosong
    if (head == nullptr) {
        newNode->next = newNode; // menunjuk ke dirinya sendiri (circular)
        return newNode;
    }

    // Cari node terakhir
    BarangNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    // Hubungkan node terakhir ke node baru
    temp->next = newNode;
    newNode->next = head;

    return head;
}

// Fungsi untuk menampilkan semua barang dalam Circular Linked List
void tampilkanStokSembako(BarangNode* head) {
    // Base case: jika linked list kosong
    if (head == nullptr) {
        cout << "Gudang kosong." << endl;
        return;
    }

    BarangNode* temp = head;

    // Traversal circular linked list
    // Menggunakan do-while agar minimal 1 node tetap diproses
    do {
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl;
        temp = temp->next;
    } while (temp != head); // berhenti saat kembali ke head
}

int main() {
    BarangNode* head = nullptr;

    // Menambahkan data barang
    head = tambahBarang(head, "Beras", 50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir", 20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    // Menampilkan daftar stok
    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head);

    return 0;
}