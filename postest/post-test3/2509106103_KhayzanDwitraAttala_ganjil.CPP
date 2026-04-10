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
        if ((arr + i)->nama == key) {
            cout << "\nHewan ditemukan: ID " << (arr + i)->id
                 << " | Nama: " << (arr + i)->nama
                 << " | Jenis: " << (arr + i)->jenis
                 << " | Harga: " << (arr + i)->harga << endl;
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
        int i = min(offset + fibMMm2, n - 1);
        cout << "Iterasi " << iterasi << ": cek ID " << (arr + i)->id << endl;
        iterasi++;

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

    if (fibMMm1 && offset + 1 < n && (arr + offset + 1)->id == x)
        return offset + 1;

    return -1;
}

void bubbleSort(Hewan* arr, int n) {
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

int cariIndexHewanById(Hewan* arr, int n, int id) {
    for (int i = 0; i < n; i++) {
        if ((arr + i)->id == id) {
            return i;
        }
    }
    return -1;
}

void enqueue(AntrianPasien* queue, int& front, int& rear, int maxSize, Hewan* arr, int n) {
    if (rear >= maxSize - 1) {
        cout << "\nAntrian penuh.\n";
        return;
    }

    int id;
    cout << "\nMasukkan ID hewan yang akan masuk antrian: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = cariIndexHewanById(arr, n, id);
    if (idx == -1) {
        cout << "ID hewan tidak ditemukan pada data.\n";
        return;
    }

    if (rear == -1) {
        front = 0;
        rear = 0;
    } else {
        rear++;
    }

    queue[rear].id = arr[idx].id;
    queue[rear].nama = arr[idx].nama;

    cout << "Hewan berhasil masuk antrian: "
         << queue[rear].nama << " (ID: " << queue[rear].id << ")\n";
}

void enqueueDarurat(AntrianPasien* queue, int& front, int& rear, int maxSize, Hewan* arr, int n) {
    if (rear >= maxSize - 1) {
        cout << "\nAntrian penuh. Tidak bisa menambahkan pasien darurat.\n";
        return;
    }

    int id;
    cout << "\nMasukkan ID hewan DARURAT: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = cariIndexHewanById(arr, n, id);
    if (idx == -1) {
        cout << "ID hewan tidak ditemukan pada data.\n";
        return;
    }

    if (rear == -1) {
        front = 0;
        rear = 0;
        queue[front].id = arr[idx].id;
        queue[front].nama = arr[idx].nama;
    } else {
        rear++;
        for (int i = rear; i > front; i--) {
            queue[i] = queue[i - 1];
        }
        queue[front].id = arr[idx].id;
        queue[front].nama = arr[idx].nama;
    }

    cout << "Pasien DARURAT berhasil dimasukkan ke paling depan antrian: "
         << queue[front].nama << " (ID: " << queue[front].id << ")\n";
}

void tampilAntrian(AntrianPasien* queue, int front, int rear) {
    cout << "\n=== Antrian Pemeriksaan (Front -> Rear) ===\n";
    if (front > rear || rear == -1) {
        cout << "Antrian kosong.\n";
        return;
    }

    AntrianPasien* p = queue + front;
    while (p <= queue + rear) {
        cout << "ID: " << p->id << " | Nama: " << p->nama << endl;
        p++;
    }
}

bool dequeue(AntrianPasien* queue, int& front, int& rear, AntrianPasien& pasienKeluar) {
    if (front > rear || rear == -1) {
        cout << "\nAntrian kosong. Tidak ada pasien untuk dipanggil.\n";
        return false;
    }

    pasienKeluar = queue[front];
    cout << "\nPasien dipanggil untuk diperiksa:\n";
    cout << "Nama: " << pasienKeluar.nama << " | ID: " << pasienKeluar.id << endl;

    front++;

    if (front > rear) {
        front = 0;
        rear = -1;
    }

    return true;
}

void pushRiwayat(RiwayatTindakan* stack, int& top, int maxSize, AntrianPasien pasien) {
    if (top >= maxSize - 1) {
        cout << "Stack riwayat penuh.\n";
        return;
    }

    string tindakan;
    cout << "Masukkan tindakan medis untuk " << pasien.nama << ": ";
    getline(cin, tindakan);

    top++;
    stack[top].id = pasien.id;
    stack[top].nama = pasien.nama;
    stack[top].tindakan = tindakan;

    cout << "Riwayat tindakan berhasil dicatat.\n";
}

void popRiwayat(RiwayatTindakan* stack, int& top) {
    if (top == -1) {
        cout << "\nRiwayat tindakan kosong.\n";
        return;
    }

    cout << "\nTindakan terakhir dihapus:\n";
    cout << "ID: " << stack[top].id
         << " | Nama: " << stack[top].nama
         << " | Tindakan: " << stack[top].tindakan << endl;
    top--;
}

void peekData(AntrianPasien* queue, int front, int rear, RiwayatTindakan* stack, int top) {
    cout << "\n=== Peek Data ===\n";

    if (front <= rear && rear != -1) {
        cout << "Pasien terdepan antrian:\n";
        cout << "ID: " << queue[front].id
             << " | Nama: " << queue[front].nama << endl;
    } else {
        cout << "Antrian kosong.\n";
    }

    if (top != -1) {
        cout << "Tindakan terakhir di riwayat:\n";
        cout << "ID: " << stack[top].id
             << " | Nama: " << stack[top].nama
             << " | Tindakan: " << stack[top].tindakan << endl;
    } else {
        cout << "Riwayat tindakan kosong.\n";
    }
}

void tampilRiwayat(RiwayatTindakan* stack, int top) {
    cout << "\n=== Riwayat Tindakan Medis ===\n";
    if (top == -1) {
        cout << "Riwayat masih kosong.\n";
        return;
    }

    RiwayatTindakan* p = stack;
    while (p <= stack + top) {
        cout << "ID: " << p->id
             << " | Nama: " << p->nama
             << " | Tindakan: " << p->tindakan << endl;
        p++;
    }
}

int main() {
    Hewan arr[MAX_DATA];
    int n = 0;
    int pilihan;

    AntrianPasien queue[MAX_ANTRIAN];
    int front = 0, rear = -1;

    RiwayatTindakan stack[MAX_RIWAYAT];
    int top = -1;

    do {
        cout << "\n=== Menu Pawcare Petshop & Klinik Hewan ===\n";
        cout << "1. Tampil semua data hewan\n";
        cout << "2. Tambah data hewan\n";
        cout << "3. Cari hewan (Linear Search - Nama)\n";
        cout << "4. Cari hewan (Fibonacci Search - ID)\n";
        cout << "5. Urutkan berdasarkan Nama (Bubble Sort)\n";
        cout << "6. Urutkan berdasarkan Harga (Selection Sort)\n";
        cout << "7. Urutkan berdasarkan ID (untuk Fibonacci Search)\n";
        cout << "8. Enqueue antrian pemeriksaan\n";
        cout << "9. Enqueue hewan darurat (prioritas depan)\n";
        cout << "10. Dequeue / panggil pasien\n";
        cout << "11. Peek antrian & riwayat\n";
        cout << "12. Tampil semua antrian\n";
        cout << "13. Tampil semua riwayat tindakan\n";
        cout << "14. Pop riwayat tindakan terakhir\n";
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
                cout << "\nHewan ditemukan: ID " << (arr + idx)->id
                     << " | Nama: " << (arr + idx)->nama
                     << " | Jenis: " << (arr + idx)->jenis
                     << " | Harga: " << (arr + idx)->harga << endl;
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
        else if (pilihan == 8) {
            if (n == 0) {
                cout << "\nBelum ada data hewan. Tambahkan data hewan terlebih dahulu.\n";
                continue;
            }
            enqueue(queue, front, rear, MAX_ANTRIAN, arr, n);
        }
        else if (pilihan == 9) {
            if (n == 0) {
                cout << "\nBelum ada data hewan. Tambahkan data hewan terlebih dahulu.\n";
                continue;
            }
            enqueueDarurat(queue, front, rear, MAX_ANTRIAN, arr, n);
        }
        else if (pilihan == 10) {
            AntrianPasien pasienDipanggil;
            if (dequeue(queue, front, rear, pasienDipanggil)) {
                pushRiwayat(stack, top, MAX_RIWAYAT, pasienDipanggil);
            }
        }
        else if (pilihan == 11) {
            peekData(queue, front, rear, stack, top);
        }
        else if (pilihan == 12) {
            tampilAntrian(queue, front, rear);
        }
        else if (pilihan == 13) {
            tampilRiwayat(stack, top);
        }
        else if (pilihan == 14) {
            popRiwayat(stack, top);
        }
        else if (pilihan != 0) {
            cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    cout << "\nTerima kasih telah menggunakan Pawcare Petshop!\n";
    return 0;
}