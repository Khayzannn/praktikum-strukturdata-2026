#include <iostream>
#include <utility>

std::pair<int,int> FindMin(const int A[], int n) {
    // Asumsi: n >= 1
    int mn = A[0];
    int minIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (A[i] < mn) {
            mn = A[i];
            minIndex = i;
        }
    }
    return std::make_pair(mn, minIndex);
}

int main() {
    // Array Fibonacci (8 elemen)
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    const int n = 8;

    auto result = FindMin(A, n);
    int minimum = result.first;
    int index  = result.second;

    std::cout << "Nilai minimum: " << minimum << std::endl;
    std::cout << "Indeks minimum: " << index << std::endl;

    return 0;

}

//Dikarenakan ada dua elemen angka minimum yang sama yaitu 1, 
//maka fungsi FindMin akan mengembalikan nilai minimum pertama
// yang ditemukan yaitu 1 dengan indeks 0 karena kondisi pembaruan adalah ketika
//  A[i] < mn, sehingga hanya akan memperbarui nilai minimum dan indeksnya
// jika ditemukan nilai yang lebih kecil dari nilai minimum saat ini.