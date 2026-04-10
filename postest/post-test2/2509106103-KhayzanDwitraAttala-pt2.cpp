#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
};

const int MAX_DATA = 100;

void tampilData(Hewan* arr, int n) {
    if (n == 0) {
        cout << "\n=== Data Hewan Pawcare Petshop ===\n";
        cout << "Belum ada data hewan.\n";
        return;
    }
    cout << "\n=== Data Hewan Pawcare Petshop ===\n";
    for (int i = 0; i < n; i++) {
        Hewan* p = arr + i;
        cout << "ID: " << p->id
             << " | Nama: " << p->nama
             << " | Jenis: " << p->jenis
             << " | Harga: " << p->harga << endl;
    }
}

void tambahData(Hewan* arr, int& n) {
    if (n >= MAX_DATA) {
        cout << "\nMaaf, data sudah penuh (maksimal " << MAX_DATA << " data).\n";
        return;
    }
    
    cout << "\nMasukkan ID: ";
    cin >> arr[n].id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Masukkan Nama: ";
    getline(cin, arr[n].nama);
    
    cout << "Masukkan Jenis: ";
    getline(cin, arr[n].jenis);
    
    cout << "Masukkan Harga: ";
    cin >> arr[n].harga;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    n++;
    cout << "Data berhasil ditambahkan!\n";
}

void linearSearch(Hewan* arr, int n, string key) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if ((arr+i)->nama == key) {
            cout << "\nHewan ditemukan: ID " << (arr+i)->id 
                 << " | Nama: " << (arr+i)->nama 
                 << " | Jenis: " << (arr+i)->jenis 
                 << " | Harga: " << (arr+i)->harga << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "\nData tidak ditemukan.\n";
}

int fibonacciSearch(Hewan* arr, int n, int x) {
    
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    int iterasi = 1;
    
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n-1);
        cout << "Iterasi " << iterasi << ": cek ID " << (arr+i)->id << endl;
        iterasi++;

        if ((arr+i)->id < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if ((arr+i)->id > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && offset + 1 < n && (arr+offset+1)->id == x) 
        return offset+1;
    
    return -1;
}

void bubbleSort(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((arr+j)->nama > (arr+j+1)->nama) {
                Hewan temp = *(arr+j);
                *(arr+j) = *(arr+j+1);
                *(arr+j+1) = temp;
            }
        }
    }
}

void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if ((arr+j)->harga < (arr+minIdx)->harga) {
                minIdx = j;
            }
        }
        Hewan temp = *(arr+minIdx);
        *(arr+minIdx) = *(arr+i);
        *(arr+i) = temp;
    }
}

void selectionSortId(Hewan* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if ((arr+j)->id < (arr+minIdx)->id) {
                minIdx = j;
            }
        }
        Hewan temp = *(arr+minIdx);
        *(arr+minIdx) = *(arr+i);
        *(arr+i) = temp;
    }
}

int main() {
    Hewan arr[MAX_DATA];
    int n = 0;
    int pilihan;

    do {
        cout << "\n=== Menu Pawcare Petshop ===\n";
        cout << "1. Tampil semua data\n";
        cout << "2. Tambah data hewan\n";
        cout << "3. Cari hewan (Linear Search - Nama)\n";
        cout << "4. Cari hewan (Fibonacci Search - ID)\n";
        cout << "5. Urutkan berdasarkan Nama (Bubble Sort)\n";
        cout << "6. Urutkan berdasarkan Harga (Selection Sort)\n";
        cout << "7. Urutkan berdasarkan ID (untuk Fibonacci Search)\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihan == 1) {
            tampilData(arr, n);
        }
        else if (pilihan == 2) {
            tambahData(arr, n);
        }
        else if (pilihan == 3) {
            string key;
            cout << "Masukkan nama hewan: ";
            getline(cin, key);
            linearSearch(arr, n, key);
        }
        else if (pilihan == 4) {
            if (n == 0) {
                cout << "\nBelum ada data hewan.\n";
                continue;
            }
            selectionSortId(arr, n);
            cout << "\nData diurutkan berdasarkan ID untuk Fibonacci Search.\n";
            
            int id;
            cout << "Masukkan ID hewan: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            int idx = fibonacciSearch(arr, n, id);
            if (idx != -1) {
                cout << "\nHewan ditemukan: ID " << (arr+idx)->id 
                     << " | Nama: " << (arr+idx)->nama 
                     << " | Jenis: " << (arr+idx)->jenis 
                     << " | Harga: " << (arr+idx)->harga << endl;
            } else {
                cout << "\nData tidak ditemukan.\n";
            }
        }
        else if (pilihan == 5) {
            if (n == 0) {
                cout << "\nBelum ada data untuk diurutkan.\n";
                continue;
            }
            bubbleSort(arr, n);
            cout << "\nData berhasil diurutkan berdasarkan Nama.\n";
        }
        else if (pilihan == 6) {
            if (n == 0) {
                cout << "\nBelum ada data untuk diurutkan.\n";
                continue;
            }
            selectionSortHarga(arr, n);
            cout << "\nData berhasil diurutkan berdasarkan Harga.\n";
        }
        else if (pilihan == 7) {
            if (n == 0) {
                cout << "\nBelum ada data untuk diurutkan.\n";
                continue;
            }
            selectionSortId(arr, n);
            cout << "\nData berhasil diurutkan berdasarkan ID.\n";
        }
        else if (pilihan != 0) {
            cout << "\nPilihan tidak valid!\n";
        }
        
    } while (pilihan != 0);

    cout << "\nTerima kasih telah menggunakan Pawcare Petshop!\n";
    return 0;
}