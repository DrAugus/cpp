//
// Created by AUGUS on 2022/8/18.
//

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <cmath>
#include <vector>

#ifndef USE_CIN
//#define USE_CIN 0
#endif

class BadLengthException {
private :
    int len;
public :
    BadLengthException() = default;

    explicit BadLengthException(int len) {
        this->len = len;
    }

    [[nodiscard]] int what() const {
        return len;
    }
};


bool checkUsername(std::string username) {
    bool isValid = true;
    int n = username.length();
    if (n < 5) {
        throw BadLengthException(n);
    }
    for (int i = 0; i < n - 1; i++) {
        if (username[i] == 'w' && username[i + 1] == 'w') {
            isValid = false;
        }
    }
    return isValid;
}

void catchUsername(std::string username) {
    try {
        bool isValid = checkUsername(username);
        if (isValid) {
            std::cout << "Valid" << '\n';
        } else {
            std::cout << "Invalid" << '\n';
        }
    } catch (BadLengthException e) {
        std::cout << "Too short: " << e.what() << '\n';
    }
}

void exception1() {
#ifdef USE_CIN
    int T;
    std::cin >> T;
    // 3
    // Peter
    // Me
    // Arxwwz
    while (T--) {
        std::string username;
        std::cin >> username;
        catchUsername(username);
    }
#else
    int T = 3;
    std::string s[3] = {"Peter", "Me", "Arxwwz"};
    while (T--) {
        catchUsername(s[T]);
    }
#endif
}


class Server {
private:
    static int load;
public:
    static int compute(long long A, long long B) {
        load += 1;
        if (A < 0) {
            throw std::invalid_argument("A is negative");
        }
        std::vector<int> v(A, 0);
        int real = -1, cmplx = std::sqrt(-1);
        if (B == 0) throw 0;
        real = (A / B) * real;
        int ans = v.at(B);
        return real + A - B * ans;
    }

    static int getLoad() {
        return load;
    }
};

int Server::load = 0;

void exception2() {
#ifdef USE_CIN
    int T;
    std::cin >> T;
    //2
    //-8 5
    //1435434255433 5
    while (T--) {
        long long A, B;
        std::cin >> A >> B;
        try {
            std::cout << Server::compute(A, B) << std::endl;
        }
        catch (std::bad_alloc &e) {
            std::cout << "Not enough memory" << std::endl;
        }
        catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Other Exception" << std::endl;
        }
    }
    std::cout << Server::getLoad() << std::endl;
#else
    int T = 2;
    long long ll[2][2] = {{-8,            5},
                          {1435434255433, 5}};
    while (T--) {
        long long A = ll[T][0], B = ll[T][1];
        try {
            std::cout << Server::compute(A, B) << std::endl;
        }
        catch (std::bad_alloc &e) {
            std::cout << "Not enough memory" << std::endl;
        }
        catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Other Exception" << std::endl;
        }
    }
    std::cout << Server::getLoad() << std::endl;
#endif
}

int main() {

    exception1();
    exception2();

    return 0;
}