//
// Created by AUGUS on 2022/8/8.
//

#include <iostream>

class Box {
private:
    int l;
    int b;
    int h;
public:
    Box() : l(0), b(0), h(0) {}

    Box(int length, int breadth, int height) : l(length), b(breadth), h(height) {}

    Box(const Box &B) : l(B.l), b(B.b), h(B.h) {}

    int getLength() { return l; }

    int getBreadth() { return b; }

    int getHeight() { return h; }

    long long CalculateVolume() const { return (long long) l * b * h; }

    bool operator<(const Box &B) {
        return (this->l < B.l || (this->b < B.b && this->l == B.l) ||
                (this->h < B.h && this->b == B.b && this->l == B.l));
    };

    Box operator+(const Box &B) {
        Box temp;
        temp.l = this->l + B.l;
        temp.b = this->b + B.b;
        temp.h = this->h + B.h;
        return temp;
    }

    friend std::ostream &operator<<(std::ostream &s, Box &B) {
        s << B.l << " " << B.b << " " << B.h;
        return s;
    }
};

int main() {
    return 1;
}