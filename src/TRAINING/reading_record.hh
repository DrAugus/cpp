//
// Created by AUGUS on 2021/5/13.
//

#ifndef AUGUSTEST_READING_RECORD_HH
#define AUGUSTEST_READING_RECORD_HH

#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>

namespace cpp_primer {

namespace basic_type {

int test();

}//namespace basic_type

namespace op3 {
//字符串 向量 数组 操作
//sting vector

int withCinTest();

int otherTest();

}//namespace op3

namespace expression {

int test();

}//namespace expression


namespace function_part {

int exinren(int, int, float);

std::string::size_type find_char(const std::string &s, char c, std::string::size_type &occurs);

void print(const int *);
void print(const int[]);
void print(const int[10]);

//数组形参
// 使用标记指定数组长度
void print(const char *cp);
//使用标准库规范
void print(const int *beg, const int *end);
//显示传递表示数组长度的形参
void print(const int ia[], std::size_t size);
//数组引用形参
void print(int (&arr)[10]);
//传递多维数组 看起来是二维数组 实际上形参是指向含有10个整数的数组的指针
void print(int (*matrix)[10], int rowsize);
void print(int matrix[][10], int rowsize);

void calSum(int &sum, std::initializer_list<int> ii);

char &get_value(std::string &str, std::string::size_type ix);
void lvalueUsing();

int (*fun1(int a))[10];
auto fun2(int a) -> int (*)[10];

class Record;

class Account;

Record lookup(Account *);
Record lookup(const Account *);
Record lookup(Account &);
Record lookup(const Account &);

bool lengthCompare(const std::string &, const std::string &);
bool (*pf)(const std::string &, const std::string &);

void useBigger(const std::string &, const std::string &, bool pf(const std::string &, const std::string &));//pf隐式转换指针
void useBigger(const std::string &,
               const std::string &,
               bool (*pf)(const std::string &, const std::string &));//pf显式定义 same as above

typedef bool Func(const std::string &, const std::string &);

typedef decltype(lengthCompare) Func2;//same as above
using Func = bool(const std::string &, const std::string &);//same as above
using Func2 = decltype(lengthCompare);//same as above
typedef bool (*FuncP)(const std::string &, const std::string &);

typedef decltype(lengthCompare) *FuncP2;//same as above
using FuncP = bool (*)(const std::string &, const std::string &);//same as above
using FuncP2 = decltype(lengthCompare) *;//same as above

void useBigger(const std::string &, const std::string &, Func);//自动转换为指针
void useBigger(const std::string &, const std::string &, FuncP2);//same as above

using F = int(int *, int);
using PF = int (*)(int *, int);

PF f1(int);
F *f1(int);
int (*f1(int))(int *, int);//same as PF
auto f1(int) -> int (*)(int *, int);
auto f1(int) -> PF;


int funSum(int a, int b) { return a + b; }
int funDec(int a, int b) { return a - b; }
int funMul(int a, int b) { return a * b; }
int funDiv(int a, int b) { return a / b; }


int test();
}//namespace function_part

} // namespace cpp_primer


#endif //AUGUSTEST_READING_RECORD_HH
