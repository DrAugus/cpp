//
// Created by AUGUS on 2021/12/16.
//

#include "augus/augus.h"
#include "gtest/gtest.h"

using namespace augus;

//这不就是replace吗
void augus::AugusUtils::TrimStr(std::string &s, char str) {
    std::string::size_type index = 0;
    if (!s.empty()) {
        while ((index = s.find(str, index)) != std::string::npos) {
            s.erase(index, 1);
        }
    }
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
}


/**
 * 拼接int
 */
std::string augus::JsonCombine::GetKeyValue(const std::string &str_key, int i_value) {
    char tag[] = "\"";
    char colon[] = ":";
    char value[50] = {0};

    std::string str_res;

    str_res.append(tag);
    str_res.append(str_key);
    str_res.append(tag);

    str_res.append(colon);
    sprintf(value, "%d", i_value);
    str_res.append(value);

    return str_res;
}

/**
 * 拼接float，保留3位
 */
std::string augus::JsonCombine::GetKeyValue(const std::string &str_key, float f_value) {
    char tag[] = "\"";
    char colon[] = ":";
    char value[50] = {0};

    std::string str_res;

    str_res.append(tag);
    str_res.append(str_key);
    str_res.append(tag);

    str_res.append(colon);
    sprintf(value, "%0.3f", f_value);
    str_res.append(value);

    return str_res;
}

/**
 * 拼接string
 */
std::string augus::JsonCombine::GetKeyValue(const std::string &str_key, const std::string &str_value) {
    char tag[] = "\"";
    char colon[] = ":";
    std::string str_res;

    str_res.append(tag);
    str_res.append(str_key);
    str_res.append(tag);

    str_res.append(colon);
    str_res.append(tag);
    str_res.append(str_value);
    str_res.append(tag);

    return str_res;
}

/**
 * 拼接object
 */
std::string augus::JsonCombine::GetKeyValueObject(const std::string &str_key, const std::string &str_obj) {
    char tag[] = "\"";
    char colon[] = ":";
    std::string str_res;

    str_res.append(tag);
    str_res.append(str_key);
    str_res.append(tag);

    str_res.append(colon);
    str_res.append(str_obj);

    return str_res;
}

/**
 * 拼接array
 */
std::string augus::JsonCombine::GetKeyValueArray(const std::string &str_key, const std::string &str_arr) {
    char tag[] = "\"";
    char colon[] = ":";
    std::string str_res;

    str_res.append(tag);
    str_res.append(str_key);
    str_res.append(tag);

    str_res.append(colon);
    str_res.append("[");
    str_res.append(str_arr);
    str_res.append("]");

    return str_res;
}

void augus::JsonCombine::use() {
    int value1 = 1;
    float value2 = 1.0f;
    std::string str_json_res("{");
    str_json_res.append(GetKeyValue("key1", value1));
    str_json_res.append(",");
    str_json_res.append(GetKeyValue("key2", value2));
    str_json_res.append("}");

    PrintTest(str_json_res);
}

TEST(JsonCombine, use) {
    auto JC = new augus::JsonCombine;
    JC->use();
}


//插入排序（算法中是直接交换节点，时间复杂度O（n^2）,空间复杂度O（1））
ListNode *ListSort::insertionSortList(ListNode *head) {
    // IMPORTANT: Please reset any member data you declared, as
    // the same Solution instance will be reused for each test case.
    if (head == nullptr || head->next == nullptr)return head;
    ListNode *p = head->next, *pstart = new ListNode(0), *pend = head;
    pstart->next = head; //为了操作方便，添加一个头结点
    while (p != nullptr) {
        ListNode *tmp = pstart->next, *pre = pstart;
        while (tmp != p && p->val >= tmp->val) //找到插入位置
        {
            tmp = tmp->next;
            pre = pre->next;
        }
        if (tmp == p)pend = p;
        else {
            pend->next = p->next;
            p->next = tmp;
            pre->next = p;
        }
        p = pend->next;
    }
    head = pstart->next;
    delete pstart;
    return head;
}

//选择排序（算法中只是交换节点的val值，时间复杂度O（n^2）,空间复杂度O（1））
ListNode *ListSort::selectSortList(ListNode *head) {
    // IMPORTANT: Please reset any member data you declared, as
    // the same Solution instance will be reused for each test case.
    //选择排序
    if (head == nullptr || head->next == nullptr)return head;
    ListNode *pstart = new ListNode(0);
    pstart->next = head; //为了操作方便，添加一个头结点
    ListNode *sortedTail = pstart;//指向已排好序的部分的尾部

    while (sortedTail->next != nullptr) {
        ListNode *minNode = sortedTail->next, *p = sortedTail->next->next;
        //寻找未排序部分的最小节点
        while (p != nullptr) {
            if (p->val < minNode->val)
                minNode = p;
            p = p->next;
        }
        std::swap(minNode->val, sortedTail->next->val);
        sortedTail = sortedTail->next;
    }

    head = pstart->next;
    delete pstart;
    return head;
}


//归并排序（算法交换链表节点，时间复杂度O（nlogn）,不考虑递归栈空间的话空间复杂度是O（1））
//
//首先用快慢指针的方法找到链表中间节点，然后递归的对两个子链表排序，把两个排好序的子链表合并成一条有序的链表。归并排序应该算是链表排序最佳的选择了，保证了最好和最坏时间复杂度都是nlogn，而且它在数组排序中广受诟病的空间复杂度在链表排序中也从O(n)降到了O(1)
ListNode *ListSort::mergeSortList(ListNode *head) {
    // IMPORTANT: Please reset any member data you declared, as
    // the same Solution instance will be reused for each test case.
    //链表归并排序
    if (head == NULL || head->next == NULL)return head;
    else {
        //快慢指针找到中间节点
        ListNode *fast = head, *slow = head;
        while (fast->next != NULL && fast->next->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow;
        slow = slow->next;
        fast->next = NULL;
//                fast = sortList(head);//前半段排序
//                slow = sortList(slow);//后半段排序
        return merge(fast, slow);
    }

}

// merge two sorted list to one
ListNode *ListSort::merge(ListNode *head1, ListNode *head2) {
    if (head1 == NULL)return head2;
    if (head2 == NULL)return head1;
    ListNode *res, *p;
    if (head1->val < head2->val) {
        res = head1;
        head1 = head1->next;
    } else {
        res = head2;
        head2 = head2->next;
    }
    p = res;

    while (head1 != NULL && head2 != NULL) {
        if (head1->val < head2->val) {
            p->next = head1;
            head1 = head1->next;
        } else {
            p->next = head2;
            head2 = head2->next;
        }
        p = p->next;
    }
    if (head1 != NULL)p->next = head1;
    else if (head2 != NULL)p->next = head2;
    return res;
}


//冒泡排序（算法交换链表节点val值，时间复杂度O（n^2）,空间复杂度O（1））
ListNode *ListSort::bubbleSortList(ListNode *head) {
    // IMPORTANT: Please reset any member data you declared, as
    // the same Solution instance will be reused for each test case.
    //链表快速排序
    if (head == NULL || head->next == NULL)return head;
    ListNode *p = NULL;
    bool isChange = true;
    while (p != head->next && isChange) {
        ListNode *q = head;
        isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
        for (; q->next && q->next != p; q = q->next) {
            if (q->val > q->next->val) {
                std::swap(q->val, q->next->val);
                isChange = true;
            }
        }
        p = q;
    }
    return head;
}

//对于希尔排序，因为排序过程中经常涉及到arr[i+gap]操作，其中gap为希尔排序的当前步长，这种操作不适合链表。
//
//对于堆排序，一般是用数组来实现二叉堆，当然可以用二叉树来实现，但是这么做太麻烦，还得花费额外的空间构建二叉树


ListSortPtr ListSort::instance() {
    static ListSortPtr ptr = nullptr;
    if (ptr == nullptr) {
        ptr = std::make_shared<ListSort>();
    }
    return ptr;
}


MathPtr Math::instance() {
    static MathPtr ptr = nullptr;
    if (ptr == nullptr) {
        ptr = std::make_shared<Math>();
    }
    return ptr;
}


TEST(Math, gcd) {
    auto p = Math::instance();
    EXPECT_EQ(p->gcd(49, 28), 7);
}

//常见的随机分布模板类
//均匀分布：
// uniform_int_distribution 整数均匀分
// uniform_real_distribution 浮点数均匀分布
//注意，uniform_int_distribution的随机数的范围不是半开范围[ )，而是[ ]，对于uniform_real_distribution却是半开范围[ )。
//伯努利类型分布：（仅有yes/no两种结果，概率一个p，一个1-p）
// bernoulli_distribution 伯努利分布
// binomial_distribution 二项分布
// geometry_distribution 几何分布
// negative_biomial_distribution 负二项分布
//Rate-based distributions:
// poisson_distribution 泊松分布
// exponential_distribution指数分布
// gamma_distribution 伽马分布
// weibull_distribution 威布尔分布
// extreme_value_distribution 极值分布
//正态分布相关：
// normal_distribution 正态分布
// chi_squared_distribution卡方分布
// cauchy_distribution 柯西分布
// fisher_f_distribution 费歇尔F分布
// student_t_distribution t分布
//分段分布相关：
// discrete_distribution离散分布
// piecewise_constant_distribution分段常数分布
// piecewise_linear_distribution分段线性分布
void Math::getRand() {
    //生成random_device对象sd做种子
    std::random_device sd;
    //使用种子初始化linear_congruential_engine对象，
    // 为的是使用它来做我们下面随机分布的种子以输出多个随机分布.
    // 注意这里要使用()操作符，因为minst_rand()接受的是一个值（你用srand也是给出这样的一个值）
    std::minstd_rand linearRan(sd());
    //生成01序列
    std::uniform_int_distribution<int> dis1(0, 1);
    std::cout << "\nuniform_int_distribution:";
    for (int i = 0; i < 100; i++) {
        //使用linear engine做种子，
        // 注意这里传入的不是一个值而是一个引擎:
        // 【随机分布函数需要传入一个随机数引擎作为参数，其实random_device也是一个引擎，这里把sd传入也不会出错】
        std::cout << dis1(linearRan) << " ";
    }
    std::cout << "\n";
}



