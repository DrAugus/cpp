//
// Created by AUGUS on 2021/8/9.
//

#include "ptr.hh"
#include "gtest/gtest.h"

int auto_ptr::test_shared_ptr()
{
    std::cout << "PART shared_ptr --------\n";
    int a = 10;
    std::shared_ptr<int> sptr1 = std::make_shared<int>(a);
    std::shared_ptr<int> sptr2(sptr1); //copy shared_ptr有拷贝构造
    std::cout << sptr1.use_count() << std::endl;
    //在初始化 shared_ptr 智能指针时，还可以自定义所指堆内存的释放规则，这样当堆内存的引用计数为 0 时，会优先调用我们自定义的释放规则。
    //指定 default_delete 作为释放规则
    std::shared_ptr<int> sptr3(std::vector<int>, std::default_delete<std::vector<int>>());
    //自定义释放规则
    auto deleteInt = [&](const int *p) -> void { delete[]p; };
    //初始化智能指针，并自定义释放规则
    std::shared_ptr<int> sptr4(new int[10], deleteInt);
    //即
    std::shared_ptr<int> sptr5(new int[10], [](const int *p) { delete[]p; });
    //simple op
    int b = 20;
    int *pb = &a;
    //std::shared_ptr<int> ptrb = pb;  //error
    std::shared_ptr<int> ptrb = std::make_shared<int>(b);
    sptr2 = ptrb; //assign
    pb = ptrb.get(); //获取原始指针
    sptr1.reset();//p1减1 不影响p2
    std::cout << sptr1.use_count() << std::endl;
    std::cout << sptr2.use_count() << std::endl;
    std::cout << ptrb.use_count() << std::endl;
    return 0;
}

int auto_ptr::test_unique_ptr()
{
    std::cout << "PART unique_ptr --------\n";
    std::unique_ptr<int> uptr1(new int);//unique_ptr无make_shared
    //std::unique_ptr<int> uptra2(uptr1);//unique_ptr无拷贝构造
    std::unique_ptr<int> uptr3(std::move(uptr1));
    //和 shared_ptr 指针不同，为 unique_ptr 自定义释放规则，只能采用函数对象的方式。例如：
    struct uniqueDel
        {
        void operator()(const int *p)
        {
            delete p;
        }
        };
    std::unique_ptr<int, uniqueDel> uptr4(new int, uniqueDel());
    std::unique_ptr<int, uniqueDel> uptr5(new int);
    std::cout << "uptr4.get " << uptr4.get() << std::endl;
    std::unique_ptr<int> p5(new int);
    *p5 = 10;
    // p 接收 p5 释放的堆内存
    int *p = p5.release();
    std::cout << *p << std::endl;
    //判断 p5 是否为空指针
    std::cout << (p5 ? "p5 is not nullptr" : "p5 is nullptr") << std::endl;
    std::unique_ptr<int> p6;
    //p6 获取 p 的所有权
    p6.reset(p);
    std::cout << *p6 << std::endl;
    return 0;
}

int auto_ptr::test_weak_ptr()
{
    std::cout << "PART weak_ptr --------\n";
    //weak_ptr 类型指针不会导致堆内存空间的引用计数增加或减少。
    std::weak_ptr<int> wptr1;
    const std::weak_ptr<int> &wptr2(wptr1);
    std::weak_ptr<int> wptr3((std::shared_ptr<int>()));
    const std::weak_ptr<int> &wptr4(wptr3);
    std::shared_ptr<int> wptr5(new int);
    std::weak_ptr<int> wptr6(wptr5);
    std::weak_ptr<int> wptr7(std::make_shared<int>(10));
    std::shared_ptr<int> sp1(new int(10));
    std::shared_ptr<int> sp2(sp1);
    std::weak_ptr<int> wp(sp2);
    //输出和 wp 同指向的 shared_ptr 类型指针的数量
    std::cout << wp.use_count() << std::endl;
    //释放 sp2
    sp2.reset();
    std::cout << wp.use_count() << std::endl;
    //借助 lock() 函数，返回一个和 wp 同指向的 shared_ptr 类型指针，获取其存储的数据
    std::cout << *(wp.lock()) << std::endl;
    std::cout << (wp.expired() ? "wp is expired" : "wp is not expired") << std::endl;
    return 0;
}

int auto_ptr::testAutoPtr()
{
    std::cout << "OP MOVE --------\n";
    {
        std::shared_ptr<int> sptr_move1(std::make_shared<int>(10));
        if (sptr_move1 == nullptr) { std::cout << "sptr_move1 is nullptr\n"; }
        std::unique_ptr<int> uptr_move1(new int);
        if (uptr_move1 == nullptr) { std::cout << "uptr_move1 is nullptr\n"; }
        std::shared_ptr<int> sptr_move2(std::move(sptr_move1));
        if (sptr_move1 == nullptr) { std::cout << "sptr_move1 is moved, now is nullptr\n"; }
        std::unique_ptr<int> uptr_move2(std::move(uptr_move1));
        if (uptr_move1 == nullptr) { std::cout << "uptr_move1 is moved, now is nullptr\n"; }

        std::cout << "sptr_move1.use_count" << sptr_move1.use_count() << "\n";
        std::cout << "sptr_move2.use_count" << sptr_move2.use_count() << "\n";
        sptr_move1.reset();
        std::cout << "sptr_move1.use_count" << sptr_move1.use_count() << "\n";
        std::cout << "sptr_move2.use_count" << sptr_move2.use_count() << "\n";
    }
    std::cout << "------------------\n";

    std::cout << "OP SIMPLE --------\n";
    {
        test_shared_ptr();
        test_unique_ptr();
        test_weak_ptr();
    }
    std::cout << "------------------\n";

    {
        std::shared_ptr<int> p3(new int(10));
        std::shared_ptr<int> p3_1 = std::make_shared<int>(10);
        std::shared_ptr<int> p3_2(std::make_shared<int>(10));
    }

    {
        std::weak_ptr<auto_ptr::Parent> wpp;
        std::weak_ptr<auto_ptr::Child> wpc;
        {
            std::shared_ptr<auto_ptr::Parent> p(new auto_ptr::Parent);
            std::shared_ptr<auto_ptr::Child> c(new auto_ptr::Child);
            p->setChild(c);
            c->setParent(p);
            wpp = p;
            wpc = c;
            std::cout << p.use_count() << std::endl; // 2
            std::cout << c.use_count() << std::endl; // 1
        }
        std::cout << wpp.use_count() << std::endl;  // 0
        std::cout << wpc.use_count() << std::endl;  // 0
        return 0;
    }


    return 0;
}

int main(){
    return 0;
}
