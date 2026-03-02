#include <iostream>

void swapByReference(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
int main() {
    int x, y;

    std::cout << "Masukkan dua bilangan bulat (dipisah spasi/enter): ";
    if (!(std::cin >> x >> y)) {
        std::cerr << "Input tidak valid.\n";
        return 1;
    }

    std::cout << "Sebelum pertukaran: x = " << x << ", y = " << y << '\n';

    swapByReference(x, y);

    std::cout << "Setelah pertukaran : x = " << x << ", y = " << y << '\n';

    return 0;
}