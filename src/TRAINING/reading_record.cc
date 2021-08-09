//
// Created by AUGUS on 2021/5/13.
//

#include "reading_record.hh"
#include "gtest/gtest.h"

int cpp_primer::basic_type::test()
{
    int mogui = 0;
    int mogui1 = {0};
    int mogui2{0};
    int mogui3(0);

    int ival = 1024;
    int &refVal = ival;
    refVal = 2;
    int ii = refVal;
    std::cout << ii << " " << ival;

    int ivale = 1.01;
    int &&rivale = 1.01;

    const int *const abc = &ival;
    return 0;
}

int cpp_primer::op3::withCinTest()
{
    unsigned trans_a, trans_b;
    std::cout << "百分比转化\n请分别输入a b (a/b)\n";
    std::cin >> trans_a >> trans_b;
    std::cout << (trans_a * 100) / trans_b << "%\n";
    return 0;
}

int cpp_primer::op3::otherTest()
{
    std::string::size_type abcd;

    std::string sn = "bhb";
    std::string sn2 = sn + "hell0" + "wtf";

    std::vector<std::string> findVal{"a", "b", "c", "d", "e", "f", "g", "h"};
    std::string soughtV = "c";
    auto itbegin = findVal.begin(), itend = findVal.end(),
        itmid = itbegin + (itend - itbegin) / 2;
    while (itmid != itend && *itmid != soughtV) {
        if (soughtV < *itmid) {
            itend = itmid;
        } else {
            itbegin = itmid + 1;
        }
        itmid = itbegin + (itend - itbegin) / 2;
    }
    if (itmid == itend) { return -1; }


    //指针也是迭代器
    std::cout << "\n指针也是迭代器\n";
    int arr_it[10] = {1, 3, 4, 2, 5, 32, 1, 1, 2, 3};
    int *e = &arr_it[10];
    //*p指向arr_it第一个元素 *e指向arr_it尾元素下一位置的指针
    for (int *p = arr_it; p != e; ++p) { // int *p = &arr_it[0]
        std::cout << *p << " ";
    }
    std::cout << "\n指针也是迭代器\n";
    //为了防止*e出现问题 C++11引入
    int *begin_it = std::begin(arr_it);
    int *end_it = std::end(arr_it);
    for (int *i = begin_it; i != end_it; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    std::vector<int> vec_it(std::begin(arr_it), std::end(arr_it));
    std::vector<int> sub_vec_it(arr_it + 1, arr_it + 4);


    using int_array = int[4];
    int ai[3][4] = {{3}, {4}, {9}};
    for (int_array *p = ai; p != ai + 3; ++p) {
        for (int *q = *p; q != *p + 4; ++q) {
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}

int cpp_primer::expression::test()
{

    std::cout << std::endl;

    std::default_random_engine randE;
    std::uniform_int_distribution<int> randValue(0, -1);
    const auto getValue = [&]() { return randValue(randE); };

    int findTimes = 0;
    {
        int i = getValue();
        while (i != 42) {
            ++findTimes;
            i = getValue();
        }
        std::cout << "find " << findTimes << " times\n";
    }
    {
        findTimes = 0;
        int i;
        while ((i = getValue()) != 42) {
            ++findTimes;
        }
        std::cout << "find " << findTimes << " times\n";
    }

    int arr_it[10] = {1, 3, 4, 2, 5, 32, 1, 1, 2, 3};
    std::vector<int> vec_a(std::begin(arr_it), std::end(arr_it));
    {
        auto pbeg = vec_a.begin();
        while (pbeg != vec_a.end()) {
            std::cout << *pbeg++ << " ";
        }
        std::cout << std::endl;
    }
    {
        for (auto it = vec_a.begin(); it != vec_a.end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    {
        std::string s1 = "a string", *p = &s1;
        auto n = s1.size();
        n = p->size();
        n = (*p).size();
    }
    {
        // LET ME TRY
        int *ptr;
        int ival;
        std::vector<int> vec;
        if (ptr != 0 && *ptr++) {}
        if (ival++ && ival) {}
        if (vec[ival++] < vec[ival]) {}
    }
    {
        // 一个30人的小测验
        unsigned long quiz1 = 0; //此值作为位的集合
        1UL << 27;//27号通过了测验
        quiz1 |= 1UL << 27;
        //核实之后 27号未通过
        quiz1 &= ~(1UL << 27);
        //判断27号是否通过
        bool status = quiz1 & (1UL << 27);
        std::cout << (status ? "27 pass" : "27 failed") << std::endl;

        std::cout << sizeof status << std::endl;

    }
    {
        // 0 0 0 1 1
        // 0 1 0 0 0
        unsigned long ul1 = 3, ul2 = 7;
        std::cout << (ul1 & ul2) << " " << (ul1 | ul2) << std::endl;

        if (typeid(ul1) != typeid(ul2)) {
            throw std::runtime_error(" ################## ");
        }

        std::cout << sizeof ul1 + ul2 << std::endl;

        void *p = &ul1;
        unsigned long *dp = static_cast<unsigned long *>(p);

        std::cout << *dp << std::endl;

        typeid(unsigned);
    }
    {
        //从标准输入中读取若干string对象并查找连续重复出现的单词。
        //要求记录连续出现的最大次数以及对应的单词。
        //如果这样的单词存在，输出重复出现的最大次数；
        //如果不存在，输出一条信息说明任何单词都没有连续出现过。
        //C++ Primer 第五版 5.14
        //https://blog.csdn.net/qq_42110350/article/details/113100378
        //https://blog.csdn.net/elma_tww/article/details/82430071?spm=1001.2014.3001.5501
    }
    {
        unsigned item1, item2;
        while (std::cin >> item1 >> item2) {
            try {
                std::cout << item2 / item1 << std::endl;
            } catch (std::runtime_error err) {
                std::cout << err.what() << "\nTry Again? Enter Y or N\n";
                char c;
                std::cin >> c;
                if (!std::cin || c == 'N') {
                    break;
                }
            }
        }
    }

    return 0;
}

int cpp_primer::function_part::exinren(int a, int b, float c)
{
    std::cout << a << b << c << std::endl;
    return 0;
}

// returns the index of the first occurrence of c in s
// the reference parameter occurs counts how often c occurs
std::string::size_type
cpp_primer::function_part::find_char(const std::string &s, char c, std::string::size_type &occurs)
{
    // position of the first occurrence, if any
    std::string::size_type ret = s.size();
    occurs = 0;            // set the occurrence count parameter

    for (std::string::size_type i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size()) {
                ret = i;
            }   // remember the first occurrence of c
            ++occurs;      // increment the occurrence count
        }
    }
    return ret;            // count is returned implicitly in occurs
}

void cpp_primer::function_part::print(const char *cp)
{
    if (cp) {
        while (*cp) {
            std::cout << *cp++ << "";
        }
    }
    std::cout << std::endl;
}

void cpp_primer::function_part::print(const int *beg, const int *end)
{
    while (beg != end) {
        std::cout << *beg++ << " ";
    }
    std::cout << std::endl;
}

void cpp_primer::function_part::print(const int ia[], std::size_t size)
{
    for (std::size_t i = 0; i != size; i++) {
        std::cout << ia[i] << " ";
    }
    std::cout << std::endl;
}

void cpp_primer::function_part::print(int (&arr)[10])
{
    for (auto ele : arr) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
}

void cpp_primer::function_part::calSum(int &sum, std::initializer_list<int> ii)
{
    sum = 0;
    for (const auto &iv:ii) {
        sum += iv;
    }
}

char &cpp_primer::function_part::get_value(std::string &str, std::string::size_type ix)
{
    return str[ix];
}

void cpp_primer::function_part::lvalueUsing()
{
    std::string s("a value");
    std::cout << s << std::endl;
    get_value(s, 0) = 'A';
    std::cout << s << std::endl;
}

bool cpp_primer::function_part::lengthCompare(const std::string &, const std::string &)
{
    return true;
}

void cpp_primer::function_part::useBigger(const std::string &,
                                          const std::string &,
                                          bool pf(const std::string &, const std::string &)) {}


int cpp_primer::function_part::test()
{
    std::string s;
    getline(std::cin, s);
    size_t ctr = 0;
    std::string::size_type index = find_char(s, 'o', ctr);
    std::cout << index << " " << ctr << std::endl;

    if (!ctr) {
        std::cerr << __func__ << " ERROR:" << __FILE__ << " at line " << __LINE__ << std::endl
                  << " Compiled on " << __DATE__ << " at " << __TIME__ << std::endl;
    }


    int j[2] = {0, 1};
    print("a string");
    print(std::begin(j), std::end(j));
    print(j, std::end(j) - std::begin(j));

    int sum = 0;
    calSum(sum, {2, 31, 4, 14, 5, 61, 6, 7});
    std::cout << "SUM---" << sum << std::endl;

    std::string s1, s2;
    pf = lengthCompare;
    pf = &lengthCompare;//same as above
    bool b1 = pf("hello", "goodbye");
    bool b2 = (*pf)("hello", "goodbye");//same as above
    bool b3 = lengthCompare("hello", "goodbye");//same as above
    useBigger(s1, s2, lengthCompare);

    typedef int(*pf2)(int, int);
    using p = int (*)(int, int);
    std::vector<p> vec{funSum, funDec, funMul, funDiv};
    for (auto pl : vec) {
        std::cout << pl << " ";
    }


    return 0;
}

int swap_p(int *a, int *b)
{
    int aa = *a;
    *a = *b;
    *b = aa;
    return 0;
}

int swap_p(int &a, int &b)
{
    int aa = a;
    a = b;
    b = aa;
    return 0;
}

class Y;


class X
{
    friend void f();
    void g();
public:
//    X() { f(); }
};

class Y
{
    X x;
};

int height;

class Screen
{
    using pos = std::string::size_type;
public:
    void fum(pos height);
private:
    pos height = 0;
};

void Screen::fum(pos height)
{
    int a = 5 * ::height;
}


struct AC
{

};

class AD: public AC
{

};

struct ADC: private AD
{

};


TEST(reading_record, something)
{

    void f();
    X xa;



    using pos = std::string::size_type;
    pos ht = 1, wd = 4;
    char aawfa = 'i';
    std::string whatf = std::string(ht * wd, aawfa);

    std::cout << whatf;



    cpp_primer::function_part::test();



    int a1 = 23, b1 = 45;
    std::cout << "a1 p " << &a1 << " b1 p " << &b1 << std::endl;
    swap_p(&a1, &b1);
    std::cout << "a1 " << a1 << " b1 " << b1 << std::endl;
    std::cout << "a1 p " << &a1 << " b1 p " << &b1 << std::endl;

    swap_p(a1, b1);
    std::cout << "a1 " << a1 << " b1 " << b1 << std::endl;
    std::cout << "a1 p " << &a1 << " b1 p " << &b1 << std::endl;

    std::swap(a1, b1);
    std::cout << "a1 " << a1 << " b1 " << b1 << std::endl;
    std::cout << "a1 p " << &a1 << " b1 p " << &b1 << std::endl;

    cpp_primer::expression::test();

    int i = 0;
    std::cout << i << " " << ++i << std::endl;
    std::cout << "=====\n";

    int iii = 1024;
    int j = -iii;
    std::cout << j << std::endl;

    bool bbb = true;
    bool mbbb = -bbb;
    std::cout << mbbb << std::endl;


    cpp_primer::basic_type::test();

    cpp_primer::op3::withCinTest();
    cpp_primer::op3::otherTest();


}