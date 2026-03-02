#include <iostream>  
#include <iomanip>
#include <string>


void reverseArray(int* arr, int n) {
    int* left = arr;           
    int* right = arr + n - 1; 

    while (left < right) {
        int tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        --right;
    }
}


void printArrayAndAddresses(int* arr, int n, const std::string& title) {
    std::cout << title << ":\n";
    for (int* p = arr; p < arr + n; ++p) {
        int index = static_cast<int>(p - arr);
        std::cout << "Index " << std::setw(2) << index
                  << " | Value = " << std::setw(2) << *p
                  << " | Address = " << reinterpret_cast<const void*>(p)
                  << '\n';
    }
    std::cout << std::endl;
}

int main() {

    int primes[7] = {2, 3, 5, 7, 11, 13, 17};
    const int n = 7;

  
    printArrayAndAddresses(primes, n, "Array sebelum dibalik");

   
    reverseArray(primes, n);

  
    printArrayAndAddresses(primes, n, "Array setelah dibalik");

    return 0;
}