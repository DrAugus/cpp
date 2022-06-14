//
// Created by AUGUS on 2021/6/7.
//

#include "thread_practice.hh"

#ifdef WIN_CLION

std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread() {
    if (main_thread_id == std::this_thread::get_id()) {
        std::cout << "This is the main thread.\n";
    } else {
        std::cout << "This is not the main thread.\n";
    }
}

void thread_test() {
    // template <class Rep, class Period>
    //        void sleep_for (const chrono::duration<Rep,Period>& rel_time);
    // 阻塞调用线程，一直到指定时间段后。
    std::cout << "countdown:\n";
    for (int i = 10; i > 0; --i) {
        std::cout << i << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Lift off!\n";

    is_main_thread();
    std::cout << std::this_thread::get_id() << std::endl;

    // template <class Clock, class Duration>
    //        void sleep_until (const chrono::time_point<Clock,Duration>& abs_time);
    // 阻塞调用线程，一直到指定事件
    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t(system_clock::now());

    struct std::tm *ptm = std::localtime(&tt);
    std::cout << "Current time: " << std::put_time(ptm, "%X") << '\n';

    std::cout << "Waiting for the next minute to begin...\n";
    ++ptm->tm_min;
    ptm->tm_sec = 0;
    std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

    std::cout << std::put_time(ptm, "%X") << " reached!\n";
    std::cout << std::this_thread::get_id() << std::endl;
}

int threadStart(const std::string &tName) {
    std::cout << "func[threadStart]###" << tName << std::endl;
    return 0;
}

int threadInt(int a) {
    std::cout << "func[threadInt]### - [" << a << "]\n";
    return 0;
}

int testThread() {
    std::cout << "\nBELLOW ARE THREAD TEST -------\n\n";

    std::thread t1(threadStart, " c++ 11 thread");
    int arg = 0;
    std::thread t2;
    std::thread t3(threadInt, arg + 1);
    std::thread t4(threadInt, std::ref(arg));
    std::thread t5(std::move(t4));

    auto judgeJoin = [&](std::thread &t, const std::string &tName) {
        std::cout << "Thread ID " << t.get_id() << "-" << std::this_thread::get_id()
                  << std::endl;
        if (t.joinable()) {
            std::cout << tName << " can join";
            t.join();
            std::cout << std::endl;
        } else {
            std::cout << tName << " can not join\n";
        }
    };

    judgeJoin(t1, "t1");
    judgeJoin(t2, "t2");
    judgeJoin(t3, "t3");
    judgeJoin(t4, "t4");
    judgeJoin(t5, "t5");

    std::thread t6(threadStart, "C++ 11 thread_1!");
    std::thread t7(threadStart, "C++ 11 thread_2!");
    std::cout << "current thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "before swap: "
              << " thread_1 id: " << t6.get_id() << " thread_2 id: " << t7.get_id()
              << std::endl;
    t6.swap(t7);
    std::cout << "after swap: "
              << " thread_1 id: " << t6.get_id() << " thread_2 id: " << t7.get_id()
              << std::endl;
    // t.detach();
    t6.join();
    t7.join();

    return 0;
}

void PaoA(char const *name) { std::cout << "和" << name << "看文艺电影" << std::endl; }

void PaoB(char const *name) {
    std::cout << "陪" << name << "逛街购物，我花钱" << std::endl;
}

void PaoC(char const *name) {
    std::cout << name << "，走，到军博看大炮去！" << std::endl;
}

void PaoD(char const *name) { std::cout << name << "，我们来谈人生好吗？" << std::endl; }

void PaoE(char const *name) { std::cout << name << "，川菜还是撸串？" << std::endl; }

char const *names[] = {"丁晓晓", "贾玲玲", "林子绿", "王梦", "水原希"};

using F = void (*)(char const *);

F functions[] = {PaoA, PaoB, PaoC, PaoD, PaoE};

constexpr size_t N = sizeof(names) / sizeof(names[0]);

void WeekendDate() {
    for (auto i = 0; i < N; ++i) {
        functions[i](names[i]);
    }
}

void CrazyWeekendDate() {
    std::thread trds[N];
    for (size_t i = 0; i < N; ++i) {
        auto trd = std::thread([i] { functions[i](names[i]); });
        trds[i] = move(trd);
    }

    for (auto &trd : trds) {
        trd.join();
    }
}

void threadTask() { std::cout << "this is my thread task" << std::endl; }

std::atomic<bool> ready(false);

void count1m(int id) {
    while (!ready) {  // wait until main() sets ready...
        std::this_thread::yield();
    }
    std::cout << id;
}

int thread_main() {
    std::thread threads[10];
    std::cout << "race of 10 threads that count to 1 million:\n";
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(count1m, i);
    }
    ready = true;  // go!
    for (auto &th : threads) {
        th.join();
    }
    std::cout << '\n';

    return 0;
}

int main() {
    std::thread t(threadTask);
    t.join();

    thread_test();
    testThread();
    thread_main();

    return 0;
}

#endif