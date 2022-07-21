//
// async.cpp
// Created by AUGUS on 2022/6/28.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include <unistd.h>
#include <iomanip>

std::mutex m;

struct X {
    void foo(int i, const std::string &str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }

    void bar(const std::string &str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }

    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};

template<typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end) {
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);

    RandomIt mid = beg + len / 2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}


int main() {

    auto fn = [&]() {
        auto s = std::chrono::system_clock::now();
        std::time_t c = std::chrono::system_clock::to_time_t(s);
        long long sum = 0;
        for (long long i = 0; i < 999999999; i++) {
            sum++;
        }
        auto e = std::chrono::system_clock::now();
        std::cout << std::put_time(std::localtime(&c), "%Y/%m/%d %H:%M:%S ") <<
                  std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count() << " msec ";
        std::cout << "hit thread fn \n";
    };

    for (int i = 0; i < 5; ++i) {
        std::thread th(fn);
        th.detach();
    }


    std::cout << "over fn, over ? \n";


    auto cal1 = std::async(std::launch::async, [&]() {
        auto s = std::chrono::system_clock::now();
        std::time_t c = std::chrono::system_clock::to_time_t(s);
        long long sum = 0;
        for (long long i = 0; i < 999999; i++) {
            sum++;
        }
        sleep(2);
        auto e = std::chrono::system_clock::now();
        std::cout << std::put_time(std::localtime(&c), "%Y/%m/%d %H:%M:%S ") <<
                  std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count() << " msec\n";
        return "hit first async ";
    });
    std::cout << cal1.get() << std::endl;

    for (int i = 0; i < 3; ++i) {
        auto cal = std::async(std::launch::async, [&]() {
            auto s = std::chrono::system_clock::now();
            std::time_t c = std::chrono::system_clock::to_time_t(s);
            long long sum = 0;
            for (long long i = 0; i < 999999999; i++) {
                sum++;
            }
            auto e = std::chrono::system_clock::now();
            std::cout << std::put_time(std::localtime(&c), "%Y/%m/%d %H:%M:%S ") <<
                      std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count() << " msec\n";
            return "hit circle async ";
        });
        std::cout << cal.get() << std::endl;
    }

    auto cal2 = std::async(std::launch::async, [&]() {
        auto s = std::chrono::system_clock::now();
        std::time_t c = std::chrono::system_clock::to_time_t(s);
        long long sum = 0;
        for (long long i = 0; i < 999999; i++) {
            sum++;
        }
//        sleep(1);
        auto e = std::chrono::system_clock::now();
        std::cout << std::put_time(std::localtime(&c), "%Y/%m/%d %H:%M:%S ") <<
                  std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count() << " msec\n";
        return "hit last async ";
    });
    std::cout << cal2.get() << std::endl;

    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

    X x;
    // Calls (&x)->foo(42, "Hello") with default policy:
    // may print "Hello 42" concurrently or defer execution
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // Calls x.bar("world!") with deferred policy
    // prints "world!" when a2.get() or a2.wait() is called
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // Calls X()(43); with async policy
    // prints "43" concurrently
    auto a3 = std::async(std::launch::async, X(), 43);
    a2.wait();                     // prints "world!"
    std::cout << a3.get() << '\n'; // prints "53"
} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here