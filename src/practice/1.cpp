//
// Created by AUGUS on 2021/12/27.
//

#include "augus/augus.h"

// 3.
// 编写基类B，并派生类C。分别定义两个类的对象，针对有虚函数和无虚函数两种情况，在运行时判别并打印对象所属的类的名称：
//     （1） 基类的指针指向基类对象；
//     （2） 派生类的指针指向派生类对象；
//     （3）基类的指针指向派生类对象。

struct BasicB;
using basic_sptr = std::shared_ptr<BasicB>;

struct BasicB {
    BasicB() = default;

    ~BasicB() = default;

    virtual void fucku() { std::cout << "fuck\n"; }

    void fuck2() { std::cout << "fuck2b\n"; }

    static basic_sptr instance();
};

struct SonC;
using son_sptr = std::shared_ptr<SonC>;

struct SonC : public BasicB {
    SonC() = default;

    ~SonC() = default;

    void fucku() override { std::cout << "fuck again\n"; }

    void fuck2() { std::cout << "fuck2c\n"; }

    static son_sptr instance();
};

basic_sptr BasicB::instance() {
    static basic_sptr b_sptr = nullptr;
    if (b_sptr == nullptr) {
        b_sptr = std::make_shared<BasicB>();
    }
    return b_sptr;
}

son_sptr SonC::instance() {
    static son_sptr c_sptr = nullptr;
    if (c_sptr == nullptr) {
        c_sptr = std::make_shared<SonC>();
    }
    return c_sptr;
}

std::atomic<int> atomic_int_x;
void increment_atomic() { atomic_int_x++; }

class X {
 public:
    auto f() -> int;
    auto gpr(int) -> void;
};
auto X::f() -> int { return 0; }
auto X::gpr(int) -> void {}

std::vector<int>* ppp = new std::vector<int>{1, 2, 3, 4};

class F {
 public:
    F(const std::vector<double>& vv, double* p) : v{vv}, res{p} {}
    void operator()(){};

 private:
    const std::vector<double>& v;
    double* res;
};

double f(const std::vector<double>& v){};
void g(const std::vector<double>& v, double* res){};
int comp(std::vector<double>& vec1, std::vector<double>& vec2, std::vector<double>& vec3) {
    double res1;
    double res2;
    double res3;
    std::thread t1{F{vec1, &res1}};
    std::thread t2{[&]() { res2 = f(vec2); }};
    std::thread t3{g, std::ref(vec3), &res3};
    t1.join();
    t2.join();
    t3.join();
    std::cout << res1 << " " << res2 << " " << res3 << " " << std::endl;
    return 0;
}

std::mutex mutex_x;
std::atomic<bool> atomic_bool_x;
int int_x;

void access1() {
    if (!atomic_bool_x) {
        std::lock_guard<std::mutex> lck(mutex_x);
        if (!atomic_bool_x)
            int_x = 42;
        atomic_bool_x = true;
    }  // 隐式释放mutex_x

    std::cout << int_x << std::endl;
}

void access2() {
    std::unique_lock<std::mutex> lck{mutex_x};
    int_x += 7;
    std::cout << int_x << std::endl;
}

double accum(double* s, double* e, double v) { return std::accumulate(s, e, v); }

double comp4(std::vector<double>& v) {
    if (v.size() < 10000)
        return std::accumulate(v.begin(), v.end(), 0.0);
    auto v0 = &v[0];
    auto sz = v.size();

    auto f0 = std::async(accum, v0, v0 + sz / 4, 0.0);
    auto f1 = std::async(accum, v0 + sz / 4, v0 + sz / 2, 0.0);
    auto f2 = std::async(accum, v0 + sz / 2, v0 + sz * 3 / 4, 0.0);
    auto f3 = std::async(accum, v0 + sz * 3 / 4, v0 + sz, 0.0);

    return f0.get() + f1.get() + f2.get() + f3.get();
}

double f(int) { return 22.0; }

void ff(int y, std::promise<double>& p) {
    try {
        // 异步执行f
        double res = f(y);
        p.set_value(res);
    } catch (...) {
        p.set_exception(std::current_exception());
    }
}

void user(int arg) {
    auto pro = std::promise<double>{};
    auto fut = pro.get_future();
    // 在不同线程上运行ff
    std::thread t{ff, arg, std::ref(pro)};
    double x = fut.get();
    std::cout << x << std::endl;
    t.join();
}

template <typename T>
void f(T& r) {
    auto v = r;          // v 是 T
    decltype(r) r2 = r;  // r2 是 T&
}

class Matrix {
    double* elements;

 public:
    Matrix() {}
    // 移动构造
    Matrix(Matrix&& a) noexcept {
        // 复制handle
        elements = a.elements;
        // 现在 a 的析构函数不用做任何事情了
        a.elements = nullptr;
    }
};

// Matrix operator+(const Matrix& m1, const Matrix& m2);
// void use_matrix(const Matrix& m1, const Matrix& m2) { Matrix m3 = m1 + m2; }

// 生成“智能指针”的工厂函数
template <class T, class A1>
std::shared_ptr<T> factory(A1&& a1) {
    return std::shared_ptr<T>(new T(std::forward<A1>(a1)));
}

template <class T, typename Args>
std::shared_ptr<T> factory(Args a) {
    return std::shared_ptr<T>(new T(a));
}
template <class T, typename Args>
std::unique_ptr<T> factory(Args a) {
    return std::unique_ptr<T>(new T(a));
}

template <class T>
class ClonePtr {
 private:
    T* ptr;

 public:
    // 移动构造
    ClonePtr(ClonePtr&& p) noexcept : ptr(p.ptr) {
        // 源数据清空
        p.ptr = 0;
    }
    // 移动赋值
    ClonePtr& operator=(ClonePtr&& p) {
        std::swap(ptr, p.ptr);
        // 销毁目标的旧值
        return *this;
    }
};

struct LengthInKM {
    constexpr explicit LengthInKM(double d) : val(d) {}
    constexpr double getValue() { return val; }

 private:
    double val;
};

struct LengthInMile {
    constexpr explicit LengthInMile(double d) : val(d) {}
    constexpr double getValue() { return val; }
    constexpr operator LengthInKM() { return LengthInKM(1.609344 * val); }

 private:
    double val;
};

struct LessThan {
    int& i;
    explicit LessThan(int& ii) : i(ii) {}
    bool operator()(int x) { return x < i; }
};

template <typename First, typename Second>
class pair {
    template <typename First2, typename Second2>
    explicit pair(pair<First2, Second2>&& rhs) noexcept(
        std::is_nothrow_constructible<First, First2&&>::value&& std::is_nothrow_constructible<Second, Second2&&>::value)
        : first(std::move(rhs.first)), second(std::move(rhs.second)) {}
    First first;
    Second second;
};

int main() {
    auto t0 = std::chrono::system_clock::now();

    std::string name = "sm23.56";

    std::string time = "1920-102-2.314+213";
    std::string date = "1920/20/20+213";

    auto fn = [&](const std::string& str) {
        return str.find('-') != std::string::npos || str.find('/') != std::string::npos;
    };

    if (name.find("") != std::string::npos) {
        std::cout << "have sm\n";
        int type = std::stoi(name.substr(name.size() - 1));
        std::cout << "type" << type << "\n";
    }

    std::cout << atomic_int_x << std::endl;
    increment_atomic();

    std::cout << atomic_int_x << std::endl;

    access1();
    access2();

    std::vector<double> vec_d_x = {12.41, 51.52, 14};
    std::vector<double> vec_d_x1 = {12.41, 51.52, 14};
    std::vector<double> vec_d_x2 = {12.41, 51.52, 14};
    std::vector<double> vec_d_x3 = {12.41, 51.52, 14};
    comp(vec_d_x1, vec_d_x2, vec_d_x3);

    augus::PrintTest(comp4(vec_d_x));

    std::promise<double> p_d;
    ff(2, p_d);

    user(int{99});

    LengthInKM marks[] = {LengthInMile(2.3), LengthInMile(0.76)};

    auto t1 = std::chrono::system_clock::now();
    // duration_cast 把依赖于时钟的“嘀嗒”节拍数转换为程序员选用的时间单位
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "msec\n";
    // c++20 可以直接使用 t1-t0

    return 0;
}