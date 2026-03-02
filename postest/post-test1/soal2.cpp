#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cmath>

struct Mahasiswa {
    std::string nama;
    std::string nim;
    float ipk;
};

int main() {
    const int N = 5;               
    Mahasiswa m[N];

    std::cout << "Input data " << N << " mahasiswa (Nama, NIM, IPK)\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "\nMahasiswa ke-" << (i + 1) << ":\n";

        
        std::cout << "Nama : ";
        std::getline(std::cin >> std::ws, m[i].nama);

        // Baca NIM (string)
        std::cout << "NIM  : ";
        std::getline(std::cin >> std::ws, m[i].nim);


        std::cout << "IPK  : ";
        while (!(std::cin >> m[i].ipk)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input tidak valid. Masukkan angka untuk IPK: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    float max_ipk = m[0].ipk;
    for (int i = 1; i < N; ++i) {
        if (m[i].ipk > max_ipk) {
            max_ipk = m[i].ipk;
        }
    }


    const float EPS = 1e-6f;
    std::cout << "\nMahasiswa dengan IPK tertinggi (" 
              << std::fixed << std::setprecision(2) << max_ipk << "):\n\n";
    for (int i = 0; i < N; ++i) {
        if (std::fabs(m[i].ipk - max_ipk) < EPS) {
            std::cout << "Nama: " << m[i].nama << "\n"
                      << "NIM : " << m[i].nim  << "\n"
                      << "IPK : " << std::fixed << std::setprecision(2) << m[i].ipk << "\n\n";
        }
    }

    return 0;
}
