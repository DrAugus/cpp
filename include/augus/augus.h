//
// Created by AUGUS on 2021/5/28.
// 这里是轮子
//

#ifndef AUGUS_H
#define AUGUS_H

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <climits>  // for INT_MAX
#include <cmath>    // for std::min
#include <complex>
#include <fstream>
#include <functional>  // for std::function for std::greater_equal
#include <future>
#include <iomanip>  //using std::put_time
#include <iostream>
#include <list>  // for std::list
#include <map>   // for std::map
#include <mutex>
#include <numeric>  // std::partial_sum
#include <random>
#include <regex>
#include <set>  // for std::set
#include <shared_mutex>
#include <stack>   // for std::stack
#include <thread>  // for std::thread
#include <tuple>
#include <type_traits>    // std::is_same_v
#include <unordered_map>  // for std::unordered_map
#include <unordered_set>  // for std::unordered_set
#include <valarray>       // for std::valarray std::max_element std::min_element std::sort
#include <vector>         // for std::vector

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

namespace augus {

// The weakness of variadic templates is that they can easily lead to code bloat as N parameters
// imply N instantiations of the template.
// 变参模板的缺点是容易导致代码膨胀，因为 N 个参数意味着模板的 N 次实例化。
template <typename T, typename... Args>
void printf(const char *s, const T &value, const Args &...args) {
    while (*s) {
        if (*s == '%' && *++s != '%') {
            std::cout << value;
            return printf(++s, args...);
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}

void PrintTest() {}

template <typename T, typename... Args>
void PrintTest(std::vector<T> info, Args... args) {
    for (auto i : info) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    PrintTest(args...);
}

template <typename T, typename... Args>
void PrintTest(T info, Args... args) {
    std::cout << info << std::endl;
    PrintTest(args...);
}

template <typename T>
void PrintTest(std::vector<T> info) {
    for (auto i : info) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PrintTest(T info) {
    std::cout << info << std::endl;
}

/// Evaluate Factorial
template <typename T>
long long GetFactorial(T n) {
    long long factorial = 1;
    for (long long i = 1; i <= n; ++i) {
        factorial *= i;
    }
    return factorial;
}

template <typename T>
T GetFactorial(T num, bool Recursive) {
    if (num == 0) {
        return 1;
    } else {
        return num * GetFactorial(num - 1);
    }
}

/// Calculate the number of combinations
template <typename T>
void ComputeAllChoices(std::vector<T> &data, T n, T outLen, T startIndex, T m, T *arr, T arrIndex) {
    if (m == 0) {
        for (T i = 0; i < outLen; i++) {
            std::cout << arr[i] << "\t";
        }
        std::cout << std::endl;

        return;
    }

    T endIndex = n - m;
    for (T i = startIndex; i <= endIndex; i++) {
        arr[arrIndex] = data[i];
        ComputeAllChoices(data, n, outLen, i + 1, m - 1, arr, arrIndex + 1);
    }
}

// 命名规则 普通变量小写/下划线 类名大写所有首字母如TestName
// 类数据数据成员同普通变量如test_name但末尾要加_ 结构体数据成员同普通变量
//  https://google.github.io/styleguide/cppguide.html#Structs_vs._Classes
// 函数随意 按public首字母大写 private首词小写
// 所有类型命名 —— 类, 结构体, 类型定义 (typedef), 枚举, 类型模板参数
//   均使用相同约定, 即以大写字母开始, 每个单词首字母均大写, 不包含下划线.
class AugusUtils;

using augus_utils_sptr = std::shared_ptr<AugusUtils>;

class AugusUtils {
 public:
    void TrimStr(std::string &s, char str);

    static std::string HandleDateTail(std::string &str);

 private:
    int test_name_;

 public:
    AugusUtils() = default;

    ~AugusUtils() = default;

    AugusUtils(const AugusUtils &) = delete;

    void operator=(const AugusUtils &) = delete;

    // instance
 public:
    static augus_utils_sptr instance();
    // inline
 public:
    bool FindTargetString(const std::string &str, const std::string &tag) { return str.find(tag) != std::string::npos; }
};

class JsonCombine {
 public:
    // 拼接int
    std::string GetKeyValue(const std::string &sKey, int iValue);

    // 拼接float，保留3位
    std::string GetKeyValue(const std::string &sKey, float fValue);

    // 拼接string
    std::string GetKeyValue(const std::string &sKey, const std::string &sValue);

    // 拼接object
    std::string GetKeyValueObject(const std::string &sKey, const std::string &sObject);

    // 拼接array
    std::string GetKeyValueArray(const std::string &sKey, const std::string &sArray);

 public:
    void use();

 public:
    JsonCombine() = default;

    ~JsonCombine() = default;

    JsonCombine(const JsonCombine &) = delete;

    void operator=(const JsonCombine &) = delete;
};

class ListSort;

using ListSortPtr = std::shared_ptr<ListSort>;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};  // struct ListNode

class ListSort : public std::enable_shared_from_this<ListSort> {
 public:
    // 插入排序（算法中是直接交换节点，时间复杂度O（n^2）,空间复杂度O（1））
    ListNode *insertionSortList(ListNode *head);

    // 选择排序（算法中只是交换节点的val值，时间复杂度O（n^2）,空间复杂度O（1））
    ListNode *selectSortList(ListNode *head);

    // 归并排序（算法交换链表节点，时间复杂度O（nlogn）,不考虑递归栈空间的话空间复杂度是O（1））
    //
    // 首先用快慢指针的方法找到链表中间节点，然后递归的对两个子链表排序，把两个排好序的子链表合并成一条有序的链表。归并排序应该算是链表排序最佳的选择了，保证了最好和最坏时间复杂度都是nlogn，而且它在数组排序中广受诟病的空间复杂度在链表排序中也从O(n)降到了O(1)
    ListNode *mergeSortList(ListNode *head);

    // merge two sorted list to one
    ListNode *merge(ListNode *head1, ListNode *head2);

    // 冒泡排序（算法交换链表节点val值，时间复杂度O（n^2）,空间复杂度O（1））
    ListNode *bubbleSortList(ListNode *head);
    // 对于希尔排序，因为排序过程中经常涉及到arr[i+gap]操作，其中gap为希尔排序的当前步长，这种操作不适合链表。
    //
    // 对于堆排序，一般是用数组来实现二叉堆，当然可以用二叉树来实现，但是这么做太麻烦，还得花费额外的空间构建二叉树

 public:
    static ListSortPtr instance();

    ListSort() = default;

    ~ListSort() = default;

    ListSort(const ListSort &) = delete;

    void operator=(const ListNode &) = delete;
};

struct Random {
    void randomTime() {
        uint32_t timeSeed = time(nullptr);

        std::string aa = "12:13:31";
        time_t tmH, tmM, tmS;
        std::default_random_engine randH, randM, randS;
        randH.seed(timeSeed);
        randM.seed(timeSeed);
        randS.seed(timeSeed);
        std::uniform_int_distribution<time_t> randTimeH{0, 23}, randTimeM(0, 59), randTimeS(0, 59);
        tmH = randTimeH(randH);
        tmM = randTimeM(randM);
        tmS = randTimeS(randS);

        std::string strH = (tmH < 10) ? ("0" + std::to_string(tmH)) : std::to_string(tmH);
        std::string strM = (tmM < 10) ? ("0" + std::to_string(tmM)) : std::to_string(tmM);
        std::string strS = (tmS < 10) ? ("0" + std::to_string(tmS)) : std::to_string(tmS);

        std::cout << strH + strM + strS;
    }
};

struct Regex {
    void regexTime() {
        try {
            std::regex rex("^([0-1]?[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$");
            //        std::regex  rex("([0-9]+):([0-9]+):([0-9]+)");
            //        std::regex rex("([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2})");
            std::string input = "11:23:12";

            std::smatch smatch1;
            while (std::cin >> input) {
                if (std::regex_search(input, smatch1, rex)) {
                    if (!smatch1.empty()) {
                        std::cout << "match\n";
                    } else {
                        std::cout << "err\n";
                    }
                } else {
                    std::cout << "no ma\n";
                }
            }
        } catch (const std::regex_error &err) {
            std::cout << "There is an error. The error is: " << err.what() << '\n';
            if (err.code() == std::regex_constants::error_brack) {
                std::cout << "This is the code of error_brack\n";
            }
        }
    }
};

class Math;

using MathPtr = std::shared_ptr<Math>;

class Math : public std::enable_shared_from_this<Math> {
 public:
    Math() = default;

    virtual ~Math() = default;

    Math(const Math &) = delete;

    Math &operator=(const Math &) = delete;

 public:
    static MathPtr instance();

 public:
    // 最大公约数
    int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }

    void getRand();
};  // class Math

class Point {
 protected:
    double x;
    double y;

 public:
    Point() : x(0), y(0){};

    Point(double a, double b) : x(a), y(b){};

    double getX() const { return x; }

    double getY() const { return y; }
};  // class Point

class CalAngle : Point {
 public:
    double XAngel(Point p1, Point p2) {
        auto angle = atan2((p2.getY() - p1.getY()), (p2.getX() - p1.getX()));  /// 弧度
        return angle;
    }

    double XTheta(Point p1, Point p2) {
        auto angle = XAngel(p1, p2);
        auto theta = angle * (180 / M_PI);  /// 角度
        return theta;
    }

    /// CCW counterclockwise
    double XAngel(Point p1, Point p2, bool CCW) {
        auto angle = atan2((p1.getY() - p2.getY()), (p2.getX() - p1.getX()));  /// 弧度
        return angle;
    }

    double XTheta(Point p1, Point p2, bool CCW) {
        auto angle = XAngel(p1, p2, true);
        auto theta = angle * (180 / M_PI);  /// 角度
        return theta;
    }

    double YAngel(Point p1, Point p2) {
        auto angle = atan2((p2.getX() - p1.getX()), (p2.getY() - p1.getY()));  /// 弧度
        return angle;
    }

    double YTheta(Point p1, Point p2) {
        auto angle = XAngel(p1, p2);
        auto theta = angle * (180 / M_PI);  /// 角度
        return theta;
    }
};  // class CalAngle

}  // namespace augus

namespace basic_cpp {

class ComplexDefine {
 public:
    ComplexDefine();

    ~ComplexDefine();
};

class OPChar {
 public:
    OPChar();

    int opWchar();
};

struct OPDecltype {
    inline bool isPrimaryCard(int val) { return val == 0x31 || val == 0x4e; }

    auto newPrimary(int val) -> decltype(isPrimaryCard(val)) {
        if (val == 0x22) {
            return isPrimaryCard(val);
        }
        return false;
    }
};

class OPSwap {
 public:
    OPSwap(int *a, int *b);

    int test();
};

class SomeSort {
 public:
    int libFuc();
};
}  // namespace basic_cpp

namespace sizeof_val {
int test();
}  // namespace sizeof_val

namespace op_list {
int commonOP();

// 数组 字符串 都在这里
namespace op_array {

class Duplicate {
 public:
    bool isContainsDuplicate(const std::vector<int> &v);

    int findDuplicateElements(int *arr, int length, std::set<int> s, std::vector<int> &output);

    int Test();
};  // class Duplicate

class VectorCtrl {
 public:
    // 寻找元素在Vector的位置
    int findPosVector(std::vector<int> input, int number);

    int findVectorSub();

    // 容器vector中元素的去重
    std::vector<int> unique_element_in_vector(std::vector<int> v);

    // 两个vector求交集
    std::vector<int> vectors_intersection(std::vector<int> v1, std::vector<int> v2);

    // 两个vector求并集
    std::vector<int> vectors_set_union(std::vector<int> v1, std::vector<int> v2);
};  // class VectorCtrl

class ArrayLength {
 public:
    ArrayLength();
};  // class ArrayLength

class LC {
 public:
    // 寻找数组的中心索引
    int pivotIndex(std::vector<int> &nums);

    // 搜索插入位置
    int searchInsert(std::vector<int> &nums, int target);

    // 旋转矩阵
    void rotate(std::vector<std::vector<int>> &matrix);

    // 零矩阵
    void setZeroes(std::vector<std::vector<int>> &matrix);

    // 最长公共前缀
    std::string longestCommonPrefix(std::vector<std::string> &strs);

    void test();

};  // class LC

std::vector<int> mergeTest(std::vector<int> &nums1, unsigned m, std::vector<int> &nums2, unsigned n);

int findMaxInArray();

int commonVectorOP();

int switchArr2Vec();

//[1,2,2,3,1,4,2]
int findShortestSubArray(std::vector<int> &nums);

}  // namespace op_array
}  // namespace op_list

namespace binary_tree {
struct TreeNode {
    int value;
    int height;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : value(0), height(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int val) : value(val), height(1), left(nullptr), right(nullptr) {}

    TreeNode(int val, int h, TreeNode *left, TreeNode *right) : value(val), height(h), left(left), right(right) {}
};  // struct TreeNode

struct BinaryTree {
    void preOrderRecur(TreeNode *head);

    void inOrderRecur(TreeNode *head);

    void posOrderRecur(TreeNode *head);

    void preOrderUnRecur(TreeNode *head);

    void inOrderUnRecur(TreeNode *head);

    void posOrderUnRecur(TreeNode *head);

    int test();

};  // struct BinaryTree

class TrainingTreeNode {
 public:
    std::vector<int> preorderTraversal(TreeNode *root);

    std::vector<int> inorderTraversal(TreeNode *root);

    TreeNode *insertNode(TreeNode *root, int val);

    int getBalance(TreeNode *root);

    int getHeight(TreeNode *root);

    TreeNode *ll_rotate(TreeNode *y);

    TreeNode *rr_rotate(TreeNode *y);

    int buildAVL();
};  // class TrainingTreeNode

}  // namespace binary_tree

namespace primary_algorithms {

void reverse_array(std::vector<int> &nums, int begin, int end);

struct pa_array {
    // 删除排序数组中的重复项
    int removeDuplicates(std::vector<int> &nums, double point);  // double point means 双指针
    int removeDuplicates(std::vector<int> &nums);

    int removeDuplicates(std::vector<int> &nums, bool use_stl);

    // 买卖股票的最佳时机 II
    int maxProfit(std::vector<int> &prices);

    // 旋转数组
    void rotate(std::vector<int> &nums, int k);

    void rotate(std::vector<int> &nums, int k, double other_array);  // 临时数组
    void rotate(std::vector<int> &nums, int k, bool use_stl);

    // 存在重复元素
    bool containsDuplicate(std::vector<int> &nums);

    bool containsDuplicate(std::vector<int> &nums, bool use_stl);

    // 只出现一次的数字
    int singleNumber(std::vector<int> &nums);

    int singleNumber(std::vector<int> &nums, bool use_set);

    // 两个数组的交集 II
    std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2);

    std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2, bool use_stl);
};

}  // namespace primary_algorithms

// https://changkun.de/modern-cpp/en-us/00-preface/
namespace modern_cpp {

void usabilityEnhancements();

// 结构化绑定
std::tuple<int, double, std::string> fTuple();

// decltype 关键字是为了解决 auto 关键字只能对变量进行类型推导的缺陷而出现的。它的用法和 typeof
// 很相似
void testIsSame();

}  // namespace modern_cpp

#endif  // AUGUS_H
