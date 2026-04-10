#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    double harga;
};

struct AntrianPasien {
    int id;
    string nama;
};

struct RiwayatTindakan {
    int id;
    string nama;
    string tindakan;
};

const int MAX_DATA = 100;
const int MAX_ANTRIAN = 100;
const int MAX_RIWAYAT = 100;

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

void enqueue(AntrianPasien* queue, int& rear, int maxSize, Hewan* arr, int n) {
    if (rear >= maxSize - 1) {
        cout << "\nAntrian penuh.\n";
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

    rear++;
    queue[rear].id = arr[idx].id;
    queue[rear].nama = arr[idx].nama;

    cout << "Pasien masuk antrian: " << queue[rear].nama
         << " (ID: " << queue[rear].id << ")\n";
}

bool dequeue(AntrianPasien* queue, int& front, int& rear, AntrianPasien& pasienKeluar) {
    if (front > rear) {
        cout << "\nAntrian kosong.\n";
        return false;
    }

    pasienKeluar = queue[front];

    cout << "\n=== PASIEN DIPANGGIL ===\n";
    cout << "Nama: " << pasienKeluar.nama
         << " | ID: " << pasienKeluar.id << "\n";

    front++;

    if (front > rear) {
        front = 0;
        rear = -1;
    }

    return true;
}

void tampilAntrian(AntrianPasien* queue, int front, int rear) {
    cout << "\n=== ANTRIAN PEMERIKSAAN (FRONT -> REAR) ===\n";
    if (front > rear) {
        cout << "Antrian kosong.\n";
        return;
    }

    AntrianPasien* p = queue + front;
    while (p <= queue + rear) {
        cout << "ID: " << p->id << " | Nama: " << p->nama << "\n";
        p++;
    }
}

void pushRiwayat(RiwayatTindakan* stack, int& top, int maxSize, AntrianPasien pasien) {
    if (top >= maxSize - 1) {
        cout << "\nRiwayat penuh.\n";
        return;
    }

    string tindakan;
    cout << "Masukkan tindakan medis: ";
    getline(cin, tindakan);

    top++;
    stack[top].id = pasien.id;
    stack[top].nama = pasien.nama;
    stack[top].tindakan = tindakan;

    cout << "Riwayat tindakan berhasil disimpan.\n";
}

void popRiwayat(RiwayatTindakan* stack, int& top) {
    cout << "\n=== POP RIWAYAT ===\n";
    if (top == -1) {
        cout << "Riwayat kosong.\n";
        return;
    }

    cout << "Data yang dihapus:\n";
    cout << "ID: " << stack[top].id
         << " | Nama: " << stack[top].nama
         << " | Tindakan: " << stack[top].tindakan << "\n";

    top--;
}

void tampilRiwayat(RiwayatTindakan* stack, int top) {
    cout << "\n=== RIWAYAT TINDAKAN MEDIS ===\n";
    if (top == -1) {
        cout << "Riwayat kosong.\n";
        return;
    }

    RiwayatTindakan* p = stack;
    while (p <= stack + top) {
        cout << "ID: " << p->id
             << " | Nama: " << p->nama
             << " | Tindakan: " << p->tindakan << "\n";
        p++;
    }
}

void peekData(AntrianPasien* queue, int front, int rear, RiwayatTindakan* stack, int top) {
    cout << "\n=== PEEK ===\n";

    if (front <= rear) {
        cout << "Pasien terdepan antrian:\n";
        cout << "ID: " << queue[front].id
             << " | Nama: " << queue[front].nama << "\n";
    } else {
        cout << "Antrian kosong.\n";
    }

    if (top != -1) {
        cout << "Tindakan terakhir:\n";
        cout << "ID: " << stack[top].id
             << " | Nama: " << stack[top].nama
             << " | Tindakan: " << stack[top].tindakan << "\n";
    } else {
        cout << "Riwayat kosong.\n";
    }
}

int main() {
    Hewan dataHewan[MAX_DATA];
    int n = 0;

    AntrianPasien antrian[MAX_ANTRIAN];
    int front = 0, rear = -1;

    RiwayatTindakan riwayat[MAX_RIWAYAT];
    int top = -1;

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
            if (n == 0) {
                cout << "Belum ada data hewan. Tambahkan dulu.\n";
            } else {
                enqueue(antrian, rear, MAX_ANTRIAN, dataHewan, n);
            }
            pauseScreen();
        }
        else if (pilihan == 9) {
            AntrianPasien pasien;
            if (dequeue(antrian, front, rear, pasien)) {
                pushRiwayat(riwayat, top, MAX_RIWAYAT, pasien);
            }
            pauseScreen();
        }
        else if (pilihan == 10) {
            peekData(antrian, front, rear, riwayat, top);
            pauseScreen();
        }
        else if (pilihan == 11) {
            tampilAntrian(antrian, front, rear);
            pauseScreen();
        }
        else if (pilihan == 12) {
            tampilRiwayat(riwayat, top);
            pauseScreen();
        }
        else if (pilihan == 13) {
            popRiwayat(riwayat, top);
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

    return 0;
}