//
// Created by AUGUS on 2021/8/9.
//

#include "ptr.hh"

int auto_ptr::test_shared_ptr() {
    augus::PrintTest("--- PART shared_ptr ---", "");
    int a = 10;
    std::shared_ptr<int> s_ptr_1 = std::make_shared<int>(a);
    std::shared_ptr<int> s_ptr_2(s_ptr_1);  // copy shared_ptr有拷贝构造
    std::cout << s_ptr_1.use_count() << std::endl;
    // 在初始化 shared_ptr
    // 智能指针时，还可以自定义所指堆内存的释放规则，这样当堆内存的引用计数为 0
    // 时，会优先调用我们自定义的释放规则。 指定 default_delete 作为释放规则
    std::shared_ptr<int> s_ptr_3(std::vector<int>,
                                 std::default_delete<std::vector<int>>());
    // 自定义释放规则
    auto deleteInt = [&](const int *p) -> void { delete[] p; };
    // 初始化智能指针，并自定义释放规则
    std::shared_ptr<int> s_ptr_4(new int[10], deleteInt);
    // 即
    std::shared_ptr<int> s_ptr_5(new int[10], [](const int *p) { delete[] p; });
    // simple op
    int b = 20;
    int *pb = &a;
    // std::shared_ptr<int> ptr_b = pb;  //error
    std::shared_ptr<int> ptr_b = std::make_shared<int>(b);
    s_ptr_2 = ptr_b;   // assign
    pb = ptr_b.get();  // 获取原始指针
    auto s_ptr_6 = s_ptr_1;
    s_ptr_1.reset();  // p1减1 不影响p2
    augus::PrintTest("s_ptr_1 use_count: ", s_ptr_1.use_count());
    augus::PrintTest("s_ptr_2 use_count: ", s_ptr_2.use_count());
    augus::PrintTest("s_ptr_6 use_count: ", s_ptr_6.use_count());
    augus::PrintTest("ptr_b use_count: ", ptr_b.use_count());
    return 0;
}

int auto_ptr::test_unique_ptr() {
    augus::PrintTest("--- PART unique_ptr ---", "");
    std::unique_ptr<int> u_ptr_1(new int);  // unique_ptr无make_shared
    // std::unique_ptr<int> u_ptr_a2(u_ptr_1);//unique_ptr无拷贝构造
    std::unique_ptr<int> u_ptr_3(std::move(u_ptr_1));
    // 和 shared_ptr 指针不同，为 unique_ptr
    // 自定义释放规则，只能采用函数对象的方式。例如：
    struct uniqueDel {
        void operator()(const int *p) { delete p; }
    };
    std::unique_ptr<int, uniqueDel> u_ptr_4(new int, uniqueDel());
    std::unique_ptr<int, uniqueDel> u_ptr_5(new int);
    augus::PrintTest("u_ptr_4.get: ", u_ptr_4.get());
    std::unique_ptr<int> p5(new int);
    *p5 = 10;
    // p 接收 p5 释放的堆内存
    int *p = p5.release();
    augus::PrintTest("*p: ", *p);
    // 判断 p5 是否为空指针
    augus::PrintTest(p5 ? "p5 is not nullptr" : "p5 is nullptr", "");
    std::unique_ptr<int> p6;
    // p6 获取 p 的所有权
    p6.reset(p);
    augus::PrintTest("*p6: ", *p6);
    return 0;
}

int auto_ptr::test_weak_ptr() {
    augus::PrintTest("--- PART weak_ptr ---", "");
    // weak_ptr 类型指针不会导致堆内存空间的引用计数增加或减少。
    std::weak_ptr<int> weak_ptr_1;
    const std::weak_ptr<int> &weak_ptr_2(weak_ptr_1);
    std::weak_ptr<int> weak_ptr_3((std::shared_ptr<int>()));
    const std::weak_ptr<int> &weak_ptr_4(weak_ptr_3);
    std::shared_ptr<int> weak_ptr_5(new int);
    std::weak_ptr<int> weak_ptr_6(weak_ptr_5);
    std::weak_ptr<int> weak_ptr_7(std::make_shared<int>(10));
    std::shared_ptr<int> sp1(new int(10));
    std::shared_ptr<int> sp2(sp1);
    std::weak_ptr<int> wp(sp2);
    // 输出和 wp 同指向的 shared_ptr 类型指针的数量
    std::cout << wp.use_count() << std::endl;
    // 释放 sp2
    sp2.reset();
    std::cout << wp.use_count() << std::endl;
    // 借助 lock() 函数，返回一个和 wp 同指向的 shared_ptr 类型指针，获取其存储的数据
    std::cout << *(wp.lock()) << std::endl;
    std::cout << (wp.expired() ? "wp is expired" : "wp is not expired") << std::endl;
    return 0;
}

int auto_ptr::testAutoPtr() {
    std::cout << "OP MOVE --------\n";
    {
        std::shared_ptr<int> s_ptr_move1(std::make_shared<int>(10));
        if (s_ptr_move1 == nullptr) {
            std::cout << "s_ptr_move1 is nullptr\n";
        }
        std::unique_ptr<int> u_ptr_move1(new int);
        if (u_ptr_move1 == nullptr) {
            std::cout << "u_ptr_move1 is nullptr\n";
        }
        std::shared_ptr<int> s_ptr_move2(std::move(s_ptr_move1));
        if (s_ptr_move1 == nullptr) {
            std::cout << "s_ptr_move1 is moved, now is nullptr\n";
        }
        std::unique_ptr<int> u_ptr_move2(std::move(u_ptr_move1));
        if (u_ptr_move1 == nullptr) {
            std::cout << "u_ptr_move1 is moved, now is nullptr\n";
        }

        std::cout << "s_ptr_move1.use_count" << s_ptr_move1.use_count() << "\n";
        std::cout << "s_ptr_move2.use_count" << s_ptr_move2.use_count() << "\n";
        s_ptr_move1.reset();
        std::cout << "s_ptr_move1.use_count" << s_ptr_move1.use_count() << "\n";
        std::cout << "s_ptr_move2.use_count" << s_ptr_move2.use_count() << "\n";
    }
    std::cout << "------------------\n";

    return 0;
}

int main() {
    auto_ptr::test_shared_ptr();
    auto_ptr::test_unique_ptr();
    auto_ptr::test_weak_ptr();
    auto_ptr::testAutoPtr();

    std::shared_ptr<int> p3(new int(10));
    std::shared_ptr<int> p3_1 = std::make_shared<int>(10);
    std::shared_ptr<int> p3_2(std::make_shared<int>(10));

    std::weak_ptr<auto_ptr::Parent> wpp;
    std::weak_ptr<auto_ptr::Child> wpc;

    std::shared_ptr<auto_ptr::Parent> p(new auto_ptr::Parent);
    std::shared_ptr<auto_ptr::Child> c(new auto_ptr::Child);
    p->setChild(c);
    c->setParent(p);
    wpp = p;
    wpc = c;
    std::cout << p.use_count() << std::endl;  // 2
    std::cout << c.use_count() << std::endl;  // 1

    std::cout << wpp.use_count() << std::endl;  // 0
    std::cout << wpc.use_count() << std::endl;  // 0
    return 0;
}
