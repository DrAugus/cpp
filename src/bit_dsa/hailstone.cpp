#include <iostream>
int main(int n) {
    int length = 1;
    std::cin >> n;
    // hailstone
    while (n > 1) {
        (n % 2) ? n = n* 3 + 1 : n = n / 2;
        length++;
    }
    std::cout << length;
    return length;
}