#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

const int MAKS_DATA_KERETA = 100;
const int MAKS_RIWAYAT = 100;

struct Kereta {
    int nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int hargaTiket;
};

struct SnapshotData {
    Kereta daftarKereta[MAKS_DATA_KERETA];
    int jumlahKereta;
};

Kereta dataKereta[MAKS_DATA_KERETA];
SnapshotData dataRiwayatUndo[MAKS_RIWAYAT];
SnapshotData dataRiwayatRedo[MAKS_RIWAYAT];

void tukarDataKereta(Kereta &keretaA, Kereta &keretaB) {
    Kereta dataSementara = keretaA;
    keretaA = keretaB;
    keretaB = dataSementara;
}

void bersihkanBufferInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void kosongkanRiwayatRedo(int &topRedo) {
    topRedo = -1;
}

void simpanSnapshotKeRiwayat(SnapshotData riwayat[], int &topRiwayat, Kereta daftarKereta[], int jumlahKereta) {
    if (topRiwayat >= MAKS_RIWAYAT - 1) {
        cout << "Riwayat penuh, snapshot tidak bisa disimpan." << endl;
        return;
    }

    topRiwayat++;
    riwayat[topRiwayat].jumlahKereta = jumlahKereta;

    for (int i = 0; i < jumlahKereta; i++) {
        riwayat[topRiwayat].daftarKereta[i] = daftarKereta[i];
    }
}

bool ambilSnapshotDariRiwayat(SnapshotData riwayat[], int &topRiwayat, Kereta daftarKereta[], int &jumlahKereta) {
    if (topRiwayat < 0) {
        return false;
    }

    jumlahKereta = riwayat[topRiwayat].jumlahKereta;

    for (int i = 0; i < jumlahKereta; i++) {
        daftarKereta[i] = riwayat[topRiwayat].daftarKereta[i];
    }

    topRiwayat--;
    return true;
}

void tampilkanJadwalKereta(Kereta daftarKereta[], int jumlahKereta) {
    cout << "\n=== JADWAL KERETA API ===" << endl;
    cout << left << setw(5) << "NO"
         << setw(15) << "NAMA"
         << setw(25) << "RUTE"
         << setw(15) << "HARGA"
         << setw(15) << "KODE" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    if (jumlahKereta == 0) {
        cout << "Belum ada data kereta." << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        return;
    }

    for (int i = 0; i < jumlahKereta; i++) {
        string ruteKereta = daftarKereta[i].asal + "-" + daftarKereta[i].tujuan;

        cout << left << setw(5) << (i + 1)
             << setw(15) << daftarKereta[i].namaKereta
             << setw(25) << ruteKereta
             << setw(15) << ("Rp " + to_string(daftarKereta[i].hargaTiket))
             << setw(15) << daftarKereta[i].nomorKereta << endl;
    }

    cout << "--------------------------------------------------------------------------" << endl;
}

void tambahDataKereta(Kereta daftarKereta[], int &jumlahKereta, int &topUndo, int &topRedo) {
    if (jumlahKereta >= MAKS_DATA_KERETA) {
        cout << "DATA PENUH! Tidak bisa menambah kereta." << endl;
        return;
    }

    simpanSnapshotKeRiwayat(dataRiwayatUndo, topUndo, daftarKereta, jumlahKereta);
    kosongkanRiwayatRedo(topRedo);

    cout << "\n--- TAMBAH DATA KERETA BARU ---" << endl;

    daftarKereta[jumlahKereta].nomorKereta = jumlahKereta + 1;

    bersihkanBufferInput();

    cout << "NAMA KERETA : ";
    getline(cin, daftarKereta[jumlahKereta].namaKereta);

    cout << "ASAL        : ";
    getline(cin, daftarKereta[jumlahKereta].asal);

    cout << "TUJUAN      : ";
    getline(cin, daftarKereta[jumlahKereta].tujuan);

    cout << "HARGA TIKET : ";
    cin >> daftarKereta[jumlahKereta].hargaTiket;

    while (cin.fail()) {
        cin.clear();
        bersihkanBufferInput();
        cout << "Input harga harus angka. Masukkan lagi: ";
        cin >> daftarKereta[jumlahKereta].hargaTiket;
    }

    jumlahKereta++;
    cout << "DATA BERHASIL DITAMBAHKAN!" << endl;
}

void cariRuteSecaraLinear(Kereta daftarKereta[], int jumlahKereta, string asalDicari, string tujuanDicari) {
    cout << "\n--- MENCARI RUTE: " << asalDicari << " -> " << tujuanDicari << " ---" << endl;
    bool dataDitemukan = false;

    for (int i = 0; i < jumlahKereta; i++) {
        cout << "Iterasi ke-" << (i + 1) << ": cek "
             << daftarKereta[i].asal << " -> " << daftarKereta[i].tujuan << "... ";

        if (daftarKereta[i].asal == asalDicari && daftarKereta[i].tujuan == tujuanDicari) {
            cout << "COCOK!" << endl;
            cout << "Ditemukan pada index: " << i << endl;
            cout << "DETAIL: " << daftarKereta[i].namaKereta
                 << " (Rp " << daftarKereta[i].hargaTiket << ")" << endl;
            dataDitemukan = true;
        } else {
            cout << "TIDAK COCOK!" << endl;
        }
    }

    if (!dataDitemukan) {
        cout << "RUTE TIDAK DITEMUKAN." << endl;
    }
}

void insertionSortNomorKereta(Kereta daftarKereta[], int jumlahKereta) {
    for (int i = 1; i < jumlahKereta; i++) {
        Kereta dataKunci = daftarKereta[i];
        int j = i - 1;

        while (j >= 0 && daftarKereta[j].nomorKereta > dataKunci.nomorKereta) {
            daftarKereta[j + 1] = daftarKereta[j];
            j--;
        }

        daftarKereta[j + 1] = dataKunci;
    }
}

void cariNomorKeretaDenganJumpSearch(Kereta daftarKereta[], int jumlahKereta, int nomorKeretaDicari) {
    if (jumlahKereta == 0) {
        cout << "DATA KOSONG..." << endl;
        return;
    }

    Kereta dataKeretaSementara[MAKS_DATA_KERETA];
    for (int i = 0; i < jumlahKereta; i++) {
        dataKeretaSementara[i] = daftarKereta[i];
    }

    insertionSortNomorKereta(dataKeretaSementara, jumlahKereta);

    int panjangLompatan = (int)sqrt((double)jumlahKereta);
    if (panjangLompatan < 1) {
        panjangLompatan = 1;
    }

    int indexAwalBlok = 0;
    int indexBatasBlok = panjangLompatan;
    bool dataDitemukan = false;

    cout << "\n--- MENCARI NOMOR KERETA: " << nomorKeretaDicari << " ---" << endl;

    while (indexAwalBlok < jumlahKereta) {
        int indexAkhirBlok;
        if (indexBatasBlok < jumlahKereta) {
            indexAkhirBlok = indexBatasBlok;
        } else {
            indexAkhirBlok = jumlahKereta;
        }

        if (dataKeretaSementara[indexAkhirBlok - 1].nomorKereta >= nomorKeretaDicari) {
            break;
        }

        indexAwalBlok = indexBatasBlok;
        indexBatasBlok = indexBatasBlok + panjangLompatan;

        if (indexAwalBlok >= jumlahKereta) {
            cout << "NOMOR KERETA TIDAK ADA..." << endl;
            return;
        }
    }

    int indexAkhirPencarian;
    if (indexBatasBlok < jumlahKereta) {
        indexAkhirPencarian = indexBatasBlok;
    } else {
        indexAkhirPencarian = jumlahKereta;
    }

    for (int i = indexAwalBlok; i < indexAkhirPencarian; i++) {
        if (dataKeretaSementara[i].nomorKereta == nomorKeretaDicari) {
            cout << "Ditemukan!" << endl;
            cout << "NAMA : " << dataKeretaSementara[i].namaKereta << endl;
            cout << "RUTE : " << dataKeretaSementara[i].asal << "-" << dataKeretaSementara[i].tujuan << endl;
            cout << "HARGA: Rp " << dataKeretaSementara[i].hargaTiket << endl;
            dataDitemukan = true;
            break;
        }
    }

    if (!dataDitemukan) {
        cout << "NOMOR KERETA TIDAK ADA..." << endl;
    }
}

void gabungDataNamaKereta(Kereta daftarKereta[], int indexKiri, int indexTengah, int indexKanan) {
    int jumlahDataKiri = indexTengah - indexKiri + 1;
    int jumlahDataKanan = indexKanan - indexTengah;

    Kereta *dataBagianKiri = new Kereta[jumlahDataKiri];
    Kereta *dataBagianKanan = new Kereta[jumlahDataKanan];

    for (int i = 0; i < jumlahDataKiri; i++) {
        dataBagianKiri[i] = daftarKereta[indexKiri + i];
    }

    for (int j = 0; j < jumlahDataKanan; j++) {
        dataBagianKanan[j] = daftarKereta[indexTengah + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = indexKiri;

    while (i < jumlahDataKiri && j < jumlahDataKanan) {
        if (dataBagianKiri[i].namaKereta <= dataBagianKanan[j].namaKereta) {
            daftarKereta[k] = dataBagianKiri[i];
            i++;
        } else {
            daftarKereta[k] = dataBagianKanan[j];
            j++;
        }
        k++;
    }

    while (i < jumlahDataKiri) {
        daftarKereta[k] = dataBagianKiri[i];
        i++;
        k++;
    }

    while (j < jumlahDataKanan) {
        daftarKereta[k] = dataBagianKanan[j];
        j++;
        k++;
    }

    delete[] dataBagianKiri;
    delete[] dataBagianKanan;
}

void mergeSortBerdasarkanNama(Kereta daftarKereta[], int indexKiri, int indexKanan) {
    if (indexKiri < indexKanan) {
        int indexTengah = indexKiri + (indexKanan - indexKiri) / 2;
        mergeSortBerdasarkanNama(daftarKereta, indexKiri, indexTengah);
        mergeSortBerdasarkanNama(daftarKereta, indexTengah + 1, indexKanan);
        gabungDataNamaKereta(daftarKereta, indexKiri, indexTengah, indexKanan);
    }
}

void selectionSortBerdasarkanHarga(Kereta daftarKereta[], int jumlahKereta) {
    for (int i = 0; i < jumlahKereta - 1; i++) {
        int indexHargaTermurah = i;

        for (int j = i + 1; j < jumlahKereta; j++) {
            if (daftarKereta[j].hargaTiket < daftarKereta[indexHargaTermurah].hargaTiket) {
                indexHargaTermurah = j;
            }
        }

        if (indexHargaTermurah != i) {
            tukarDataKereta(daftarKereta[i], daftarKereta[indexHargaTermurah]);
        }
    }
}

void lakukanUndo(Kereta daftarKereta[], int &jumlahKereta, int &topUndo, int &topRedo) {
    if (topUndo < 0) {
        cout << "Tidak ada aksi yang bisa di-undo." << endl;
        return;
    }

    simpanSnapshotKeRiwayat(dataRiwayatRedo, topRedo, daftarKereta, jumlahKereta);
    ambilSnapshotDariRiwayat(dataRiwayatUndo, topUndo, daftarKereta, jumlahKereta);
    cout << "UNDO berhasil dilakukan." << endl;
}

void lakukanRedo(Kereta daftarKereta[], int &jumlahKereta, int &topUndo, int &topRedo) {
    if (topRedo < 0) {
        cout << "Tidak ada aksi yang bisa di-redo." << endl;
        return;
    }

    simpanSnapshotKeRiwayat(dataRiwayatUndo, topUndo, daftarKereta, jumlahKereta);
    ambilSnapshotDariRiwayat(dataRiwayatRedo, topRedo, daftarKereta, jumlahKereta);
    cout << "REDO berhasil dilakukan." << endl;
}

void tampilkanMenuSearch(Kereta daftarKereta[], int jumlahKereta) {
    int pilihanMenuSearch;

    do {
        cout << "\n=== MENU SEARCH ===" << endl;
        cout << "1. Cari berdasarkan RUTE" << endl;
        cout << "2. Cari berdasarkan NOMOR KERETA" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihanMenuSearch;

        while (cin.fail()) {
            cin.clear();
            bersihkanBufferInput();
            cout << "Input harus angka. Pilih lagi: ";
            cin >> pilihanMenuSearch;
        }

        switch (pilihanMenuSearch) {
            case 1: {
                string asalDicari, tujuanDicari;
                bersihkanBufferInput();

                cout << "Asal   : ";
                getline(cin, asalDicari);
                cout << "Tujuan : ";
                getline(cin, tujuanDicari);

                cariRuteSecaraLinear(daftarKereta, jumlahKereta, asalDicari, tujuanDicari);
                break;
            }

            case 2: {
                int nomorKeretaDicari;
                cout << "Masukkan nomor kereta: ";
                cin >> nomorKeretaDicari;

                while (cin.fail()) {
                    cin.clear();
                    bersihkanBufferInput();
                    cout << "Input harus angka. Masukkan lagi: ";
                    cin >> nomorKeretaDicari;
                }

                cariNomorKeretaDenganJumpSearch(daftarKereta, jumlahKereta, nomorKeretaDicari);
                break;
            }

            case 3:
                cout << "Kembali ke menu utama..." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihanMenuSearch != 3);
}

void tampilkanMenuSort(Kereta daftarKereta[], int jumlahKereta, int &topUndo, int &topRedo) {
    int pilihanMenuSort;

    do {
        cout << "\n=== MENU SORT ===" << endl;
        cout << "1. Urutkan berdasarkan NAMA KERETA" << endl;
        cout << "2. Urutkan berdasarkan HARGA TIKET" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihanMenuSort;

        while (cin.fail()) {
            cin.clear();
            bersihkanBufferInput();
            cout << "Input harus angka. Pilih lagi: ";
            cin >> pilihanMenuSort;
        }

        switch (pilihanMenuSort) {
            case 1:
                if (jumlahKereta > 0) {
                    simpanSnapshotKeRiwayat(dataRiwayatUndo, topUndo, daftarKereta, jumlahKereta);
                    kosongkanRiwayatRedo(topRedo);
                    mergeSortBerdasarkanNama(daftarKereta, 0, jumlahKereta - 1);
                    cout << "Data berhasil diurutkan berdasarkan nama kereta." << endl;
                    tampilkanJadwalKereta(daftarKereta, jumlahKereta);
                } else {
                    cout << "DATA MASIH KOSONG!" << endl;
                }
                break;

            case 2:
                if (jumlahKereta > 0) {
                    simpanSnapshotKeRiwayat(dataRiwayatUndo, topUndo, daftarKereta, jumlahKereta);
                    kosongkanRiwayatRedo(topRedo);
                    selectionSortBerdasarkanHarga(daftarKereta, jumlahKereta);
                    cout << "Data berhasil diurutkan berdasarkan harga tiket termurah." << endl;
                    tampilkanJadwalKereta(daftarKereta, jumlahKereta);
                } else {
                    cout << "DATA MASIH KOSONG!" << endl;
                }
                break;

            case 3:
                cout << "Kembali ke menu utama..." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihanMenuSort != 3);
}

int main() {
    int jumlahKereta = 0;
    int pilihanMenuUtama;
    int topUndo = -1;
    int topRedo = -1;

    dataKereta[0].nomorKereta = 1;
    dataKereta[0].namaKereta = "tirta";
    dataKereta[0].asal = "bandung";
    dataKereta[0].tujuan = "jakarta";
    dataKereta[0].hargaTiket = 500000;

    dataKereta[1].nomorKereta = 2;
    dataKereta[1].namaKereta = "argo";
    dataKereta[1].asal = "jakarta";
    dataKereta[1].tujuan = "bandung";
    dataKereta[1].hargaTiket = 450000;

    dataKereta[2].nomorKereta = 3;
    dataKereta[2].namaKereta = "wishel";
    dataKereta[2].asal = "semarang";
    dataKereta[2].tujuan = "yogyakarta";
    dataKereta[2].hargaTiket = 550000;

    jumlahKereta = 3;

    do {
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Tampilkan Jadwal Kereta" << endl;
        cout << "2. Tambah Data Kereta" << endl;
        cout << "3. Menu Search" << endl;
        cout << "4. Menu Sort" << endl;
        cout << "5. Undo" << endl;
        cout << "6. Redo" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihanMenuUtama;

        while (cin.fail()) {
            cin.clear();
            bersihkanBufferInput();
            cout << "Input harus angka. Pilih lagi: ";
            cin >> pilihanMenuUtama;
        }

        switch (pilihanMenuUtama) {
            case 1:
                tampilkanJadwalKereta(dataKereta, jumlahKereta);
                break;

            case 2:
                tambahDataKereta(dataKereta, jumlahKereta, topUndo, topRedo);
                break;

            case 3:
                tampilkanMenuSearch(dataKereta, jumlahKereta);
                break;

            case 4:
                tampilkanMenuSort(dataKereta, jumlahKereta, topUndo, topRedo);
                break;

            case 5:
                lakukanUndo(dataKereta, jumlahKereta, topUndo, topRedo);
                break;

            case 6:
                lakukanRedo(dataKereta, jumlahKereta, topUndo, topRedo);
                break;

            case 7:
                cout << "THANK YOU! BE CAREFUL..." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihanMenuUtama != 7);

    return 0;
}