//
// Created by AUGUS on 2021/1/7.
//

#ifndef AUGUSTEST_INTERVIEW_HH
#define AUGUSTEST_INTERVIEW_HH

#include <vector> // for std::vector
#include <iostream> // for std::cout
#include <algorithm> // for std::any_of
#include <ctime> // for clock_t
#include <map>
#include <mutex> // for std::mutex


namespace joyient {

//这个题已经忘记是什么了
// 应该是矩阵搜索算法

} //namespace joyient

//www.hankedata.com
namespace hanke {
//第一题 leetcode 19
//给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
//示例：
//给定一个链表: 1->2->3->4->5, 和 n = 2.
//当删除了倒数第二个节点后，链表变为 1->2->3->5.
//说明：
//给定的 n 保证是有效的。
//进阶：
//你能尝试使用一趟扫描实现吗？

namespace case1 {
// Definition for singly-linked list.
struct ListNode
{
    int val;

    ListNode *next;

    explicit ListNode(int x) : val(x), next(NULL) {}
};

class Solution1
{
private:
    std::map<int, ListNode *> mp;

public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *p = head;
        int i = 0;
        while (p) {
            mp[i++] = p;
            p = p->next;
        }
        n = i - n;
        if (n == 0) { return head->next; }
        mp[n - 1]->next = mp[n]->next;
        return head;
    }
};
}//namespace  case1




//第二题 计算输入int数值为二进制时1的个数
// https://blog.csdn.net/qq_39755395/article/details/78177804

//第三题 题目：设计一个类，我们只能生成该类的一个实例。
//分析：只能生成一个实例的类是实现了Singleton 模式的类型。


/*
72. 题目：设计一个类，我们只能生成该类的一个实例。
分析：只能生成一个实例的类是实现了Singleton 模式的类型。
1.为了防止从类的外部调用构造函数，产生类的新的实例，我们应该把该类的构造函数声明成protected或者private。
2.生成一个类的实例，我们可以考虑用静态成员函数来记录，
指向这个实例的指针声明成静态变量，存放在静态存储区，把这个类的实例用new来构造，并放在堆里。
*/

namespace case3 {
namespace no_multi_thread {
class Singleton
{
private:
    static Singleton *instance;
    Singleton() = default;
    Singleton(const Singleton &) = default;
public:
    static Singleton *GetInstance()
    {
        if (instance == nullptr) {//如果之前没有构造过，那么就构造一个新的实例。
            //如果构造过，那么就把之前构造的那个实例返回。
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton *Singleton::instance = nullptr;
}//namespace no_multi_thread



//看了别人的多线程
//如果要加入多线程的考虑。
//加入互斥量Mutex。加锁lock（）。开锁unlock（）；

namespace multi_thread {
std::mutex mu;

class Singleton
{
private:
    static Singleton *instance;
    Singleton()= default;
    Singleton(const Singleton &)= default;

public:
    static Singleton *GetInstance()
    {
        if (instance == nullptr) {
            mu.lock();
            if (instance == nullptr) {
                instance = new Singleton();
            }
            mu.unlock();
        }
        return instance;
    }
};

Singleton *Singleton::instance = nullptr;
}//namespace multi_thread

}//namespace case3

}//namespace hanke

#endif //AUGUSTEST_INTERVIEW_HH
