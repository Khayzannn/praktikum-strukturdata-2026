#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
};

struct QueueNode {
    int id;
    string nama;
    QueueNode* next;
};

struct StackNode {
    int id;
    string nama;
    string tindakan;
    StackNode* next;
};

const int MAX_DATA = 100;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void tampilJudul() {
    cout << "=========================================\n";
    cout << "   PAWCARE PETSHOP & KLINIK HEWAN\n";
    cout << "=========================================\n";
}

int cariIndexHewanById(Hewan* arr, int n, int id) {
    for (int i = 0; i < n; i++) {
        if ((arr + i)->id == id) {
            return i;
        }
    }
    return -1;
}

void tampilData(Hewan* arr, int n) {
    cout << "\n=== DATA HEWAN ===\n";
    if (n == 0) {
        cout << "Belum ada data hewan.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        Hewan* p = arr + i;
        cout << "ID: " << p->id
             << " | Nama: " << p->nama
             << " | Jenis: " << p->jenis
             << " | Harga: " << p->harga << "\n";
    }
}

void tambahData(Hewan* arr, int& n) {
    if (n >= MAX_DATA) {
        cout << "\nData sudah penuh.\n";
        return;
    }

    cout << "\n=== TAMBAH DATA HEWAN ===\n";
    cout << "Masukkan ID: ";
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
    cout << "Data berhasil ditambahkan.\n";
}

void linearSearch(Hewan* arr, int n, string key) {
    bool found = false;

    for (int i = 0; i < n; i++) {
        if ((arr + i)->nama == key) {
            cout << "\nHewan ditemukan:\n";
            cout << "ID: " << (arr + i)->id
                 << " | Nama: " << (arr + i)->nama
                 << " | Jenis: " << (arr + i)->jenis
                 << " | Harga: " << (arr + i)->harga << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nData tidak ditemukan.\n";
    }
}

void bubbleSortNama(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->nama > (arr + j + 1)->nama) {
                Hewan temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

void selectionSortHarga(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + minIdx)->harga) {
                minIdx = j;
            }
        }
        Hewan temp = *(arr + minIdx);
        *(arr + minIdx) = *(arr + i);
        *(arr + i) = temp;
    }
}

void selectionSortId(Hewan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->id < (arr + minIdx)->id) {
                minIdx = j;
            }
        }
        Hewan temp = *(arr + minIdx);
        *(arr + minIdx) = *(arr + i);
        *(arr + i) = temp;
    }
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

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if ((arr + i)->id < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if ((arr + i)->id > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && offset + 1 < n && (arr + offset + 1)->id == x) {
        return offset + 1;
    }

    return -1;
}

// ====================== QUEUE SINGLE LINKED LIST ======================

bool isQueueEmpty(QueueNode* front) {
    return front == nullptr;
}

void enqueue(QueueNode*& front, QueueNode*& rear, Hewan* arr, int n) {
    if (n == 0) {
        cout << "Belum ada data hewan.\n";
        return;
    }

    int id;
    cout << "\n=== ENQUEUE ANTRIAN ===\n";
    cout << "Masukkan ID hewan: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = cariIndexHewanById(arr, n, id);
    if (idx == -1) {
        cout << "ID hewan tidak ditemukan.\n";
        return;
    }

    QueueNode* baru = new QueueNode;
    baru->id = arr[idx].id;
    baru->nama = arr[idx].nama;
    baru->next = nullptr;

    if (isQueueEmpty(front)) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }

    cout << "Pasien masuk antrian: " << baru->nama
         << " (ID: " << baru->id << ")\n";
}

bool dequeue(QueueNode*& front, QueueNode*& rear, int& id, string& nama) {
    if (isQueueEmpty(front)) {
        cout << "\nAntrian kosong.\n";
        return false;
    }

    QueueNode* hapus = front;
    id = hapus->id;
    nama = hapus->nama;

    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }

    delete hapus;
    return true;
}

void tampilAntrian(QueueNode* front) {
    cout << "\n=== ANTRIAN PEMERIKSAAN (FRONT -> REAR) ===\n";
    if (isQueueEmpty(front)) {
        cout << "Antrian kosong.\n";
        return;
    }

    QueueNode* bantu = front;
    while (bantu != nullptr) {
        cout << "ID: " << bantu->id
             << " | Nama: " << bantu->nama << "\n";
        bantu = bantu->next;
    }
}

void peekAntrian(QueueNode* front) {
    if (isQueueEmpty(front)) {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "Pasien terdepan antrian:\n";
    cout << "ID: " << front->id
         << " | Nama: " << front->nama << "\n";
}

// ====================== STACK SINGLE LINKED LIST ======================

bool isStackEmpty(StackNode* top) {
    return top == nullptr;
}

void push(StackNode*& top, int id, string nama, string tindakan) {
    StackNode* baru = new StackNode;
    baru->id = id;
    baru->nama = nama;
    baru->tindakan = tindakan;
    baru->next = top;
    top = baru;

    cout << "Riwayat tindakan berhasil disimpan.\n";
}

void pop(StackNode*& top) {
    cout << "\n=== POP RIWAYAT ===\n";
    if (isStackEmpty(top)) {
        cout << "Riwayat kosong.\n";
        return;
    }

    StackNode* hapus = top;
    cout << "Data yang dihapus:\n";
    cout << "ID: " << hapus->id
         << " | Nama: " << hapus->nama
         << " | Tindakan: " << hapus->tindakan << "\n";

    top = top->next;
    delete hapus;
}

void tampilRiwayat(StackNode* top) {
    cout << "\n=== RIWAYAT TINDAKAN MEDIS (TOP -> BOTTOM) ===\n";
    if (isStackEmpty(top)) {
        cout << "Riwayat kosong.\n";
        return;
    }

    StackNode* bantu = top;
    while (bantu != nullptr) {
        cout << "ID: " << bantu->id
             << " | Nama: " << bantu->nama
             << " | Tindakan: " << bantu->tindakan << "\n";
        bantu = bantu->next;
    }
}

void peekRiwayat(StackNode* top) {
    if (isStackEmpty(top)) {
        cout << "Riwayat kosong.\n";
        return;
    }

    cout << "Tindakan terakhir:\n";
    cout << "ID: " << top->id
         << " | Nama: " << top->nama
         << " | Tindakan: " << top->tindakan << "\n";
}

void peekData(QueueNode* front, StackNode* top) {
    cout << "\n=== PEEK ===\n";
    peekAntrian(front);
    peekRiwayat(top);
}

// ====================== HAPUS MEMORI ======================

void hapusSemuaAntrian(QueueNode*& front, QueueNode*& rear) {
    while (front != nullptr) {
        QueueNode* hapus = front;
        front = front->next;
        delete hapus;
    }
    rear = nullptr;
}

void hapusSemuaRiwayat(StackNode*& top) {
    while (top != nullptr) {
        StackNode* hapus = top;
        top = top->next;
        delete hapus;
    }
}

// ====================== MAIN ======================

int main() {
    Hewan dataHewan[MAX_DATA];
    int n = 0;

    QueueNode* front = nullptr;
    QueueNode* rear = nullptr;

    StackNode* top = nullptr;

    int pilihan;

    do {
        clearScreen();
        tampilJudul();

        cout << "1. Tampil semua data hewan\n";
        cout << "2. Tambah data hewan\n";
        cout << "3. Cari hewan berdasarkan nama\n";
        cout << "4. Cari hewan berdasarkan ID\n";
        cout << "5. Urutkan data berdasarkan nama\n";
        cout << "6. Urutkan data berdasarkan harga\n";
        cout << "7. Urutkan data berdasarkan ID\n";
        cout << "8. Enqueue antrian pemeriksaan\n";
        cout << "9. Dequeue / panggil pasien\n";
        cout << "10. Peek antrian dan riwayat\n";
        cout << "11. Tampil semua antrian\n";
        cout << "12. Tampil semua riwayat\n";
        cout << "13. Pop riwayat tindakan terakhir\n";
        cout << "0. Keluar\n";
        cout << "-----------------------------------------\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        clearScreen();
        tampilJudul();

        if (pilihan == 1) {
            tampilData(dataHewan, n);
            pauseScreen();
        }
        else if (pilihan == 2) {
            tambahData(dataHewan, n);
            pauseScreen();
        }
        else if (pilihan == 3) {
            string key;
            cout << "Masukkan nama hewan: ";
            getline(cin, key);
            linearSearch(dataHewan, n, key);
            pauseScreen();
        }
        else if (pilihan == 4) {
            if (n == 0) {
                cout << "Belum ada data hewan.\n";
                pauseScreen();
                continue;
            }

            selectionSortId(dataHewan, n);

            int id;
            cout << "Masukkan ID hewan: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int idx = fibonacciSearch(dataHewan, n, id);
            if (idx != -1) {
                cout << "\nHewan ditemukan:\n";
                cout << "ID: " << (dataHewan + idx)->id
                     << " | Nama: " << (dataHewan + idx)->nama
                     << " | Jenis: " << (dataHewan + idx)->jenis
                     << " | Harga: " << (dataHewan + idx)->harga << "\n";
            } else {
                cout << "Data tidak ditemukan.\n";
            }
            pauseScreen();
        }
        else if (pilihan == 5) {
            if (n == 0) {
                cout << "Belum ada data untuk diurutkan.\n";
            } else {
                bubbleSortNama(dataHewan, n);
                cout << "Data berhasil diurutkan berdasarkan nama.\n";
            }
            pauseScreen();
        }
        else if (pilihan == 6) {
            if (n == 0) {
                cout << "Belum ada data untuk diurutkan.\n";
            } else {
                selectionSortHarga(dataHewan, n);
                cout << "Data berhasil diurutkan berdasarkan harga.\n";
            }
            pauseScreen();
        }
        else if (pilihan == 7) {
            if (n == 0) {
                cout << "Belum ada data untuk diurutkan.\n";
            } else {
                selectionSortId(dataHewan, n);
                cout << "Data berhasil diurutkan berdasarkan ID.\n";
            }
            pauseScreen();
        }
        else if (pilihan == 8) {
            enqueue(front, rear, dataHewan, n);
            pauseScreen();
        }
        else if (pilihan == 9) {
            int idPasien;
            string namaPasien;

            if (dequeue(front, rear, idPasien, namaPasien)) {
                cout << "\n=== PASIEN DIPANGGIL ===\n";
                cout << "Nama: " << namaPasien
                     << " | ID: " << idPasien << "\n";

                string tindakan;
                cout << "Masukkan tindakan medis: ";
                getline(cin, tindakan);

                push(top, idPasien, namaPasien, tindakan);
            }
            pauseScreen();
        }
        else if (pilihan == 10) {
            peekData(front, top);
            pauseScreen();
        }
        else if (pilihan == 11) {
            tampilAntrian(front);
            pauseScreen();
        }
        else if (pilihan == 12) {
            tampilRiwayat(top);
            pauseScreen(); 
        }
        else if (pilihan == 13) {
            pop(top);
            pauseScreen();
        }
        else if (pilihan == 0) {
            cout << "Program selesai.\n";
        }
        else {
            cout << "Pilihan tidak valid.\n";
            pauseScreen();
        }

    } while (pilihan != 0);

    hapusSemuaAntrian(front, rear);
    hapusSemuaRiwayat(top);

    return 0;
}