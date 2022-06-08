#include <iostream>
int main() {
    int length = 1;
    int n;
    std::cin >> n;
    // hailstone
    while (n > 1) {
        (n % 2) ? n = n* 3 + 1 : n = n / 2;
        length++;
    }
    std::cout << length;
    return length;
}