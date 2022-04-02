//
// Created by AUGUS on 2021/6/7.
//

#ifndef AUGUSTEST_THREAD_PRACTICE_HH
#define AUGUSTEST_THREAD_PRACTICE_HH


#include "augus/augus.h"

namespace thread_practice {
std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread();
void thread_test();

}//namespace thread_practice

namespace test_thread {

int threadStart(const std::string &tName);
int threadInt(int a);
int testThread();

}//namespace test_thread
namespace example_yield {
std::atomic<bool> ready(false);

void count1m(int id)
{
    while (!ready) { // wait until main() sets ready...
        std::this_thread::yield();
    }
    for (volatile int i = 0; i < 1000000; ++i) {}
    std::cout << id;
}

int thread_main()
{
    std::thread threads[10];
    std::cout << "race of 10 threads that count to 1 million:\n";
    for (int i = 0; i < 10; ++i) { threads[i] = std::thread(count1m, i); }
    ready = true; // go!
    for (auto &th : threads) { th.join(); }
    std::cout << '\n';

    return 0;
}

}//namespace example_yield


#endif //AUGUSTEST_THREAD_PRACTICE_HH
