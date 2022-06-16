//
// Created by AUGUS on 2021/12/27.
//

#include "augus.h"

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

double f(const std::vector<double>& v) { return 0.0; }
void g(const std::vector<double>& v, double* res) {}
#ifdef WIN_CLION
int comp(std::vector<double>& vec1, std::vector<double>& vec2,
         std::vector<double>& vec3) {
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
#endif

std::mutex mutex_x;
std::atomic<bool> atomic_bool_x;
int int_x;

// 共享锁
std::shared_mutex shared_mutex_x;
void reader_mutex() {
    // 跟其他 reader 共享访问
    std::shared_lock lck{shared_mutex_x};
    // 读
}
void writer_mutex() {
    // writer 独占
    std::unique_lock lck{shared_mutex_x};
}

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

#ifdef WIN_CLION
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
#endif

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

#ifdef WIN_CLION
void user(int arg) {
    auto pro = std::promise<double>{};
    auto fut = pro.get_future();
    // 在不同线程上运行ff
    std::thread t{ff, arg, std::ref(pro)};
    double x = fut.get();
    std::cout << x << std::endl;
    t.join();
}
#endif

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
        std::is_nothrow_constructible<First, First2&&>::value&&
            std::is_nothrow_constructible<Second, Second2&&>::value)
        : first(std::move(rhs.first)), second(std::move(rhs.second)) {}
    First first;
    Second second;
};

void pass_para(int);
void pass_para(int&);
void pass_para(const int&);
void pass_para(int&&);

template <typename T>
using Value_type = typename T::value_type;

// std::complex<double> complex_z = 2 + 3i;

union U {
    int i;
    char* p;
};

template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

using var_t = std::variant<int, long, double, std::string>;

class MagicFoo {
 public:
    std::vector<int> vec;
    MagicFoo(std::initializer_list<int> list) {
        for (int it : list) {
            vec.push_back(it);
        }
    }
};

template <typename T, typename U>
class MagicType {
 public:
    T dark;
    U magic;
};
typedef int (*process)(void*);
using NewProcess = int (*)(void*);
template <typename T>
using TruelyDarkMagic = MagicType<std::vector<T>, std::string>;

class Base {
 public:
    int value1;
    int value2{};
    Base() { value1 = 1; }
    // 委托 Base() 构造函数
    explicit Base(int value) : Base() { value2 = value; }

 public:
    virtual void foo(int);
};
void Base::foo(int) {}

class SubBase : public Base {
 public:
    // 继承构造
    using Base::Base;

 public:
    void foo(int) override;
    virtual void foo(float) final;
};
void SubBase::foo(int) {}
void SubBase::foo(float) {}

class Sub2Base final : public SubBase {};

enum class new_enum : unsigned int { value1, value2, value3 = 100, value4 = 102 };

template <typename T>
std::ostream& operator<<(
    typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream,
    const T& e) {
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
    for (auto&& [key, value] : m) value = foo(key);
}

namespace lambda_learning {
void lambda_learning() {
    std::cout << "\nLearningLambda TEST\n";
    class Simple {
     public:
        static void func() {
            auto f = [](int a) -> int { return a + 1; };
            std::cout << "Simple \n - f(1): " << f(1) << std::endl;
            //// C++11 中会根据 return 语句自动推导出返回值类型
            auto y = [](int a) { return a + 1; };
            std::cout << " - y(1): " << y(1) << std::endl;
            /// 需要注意 -> 初始化列表不能用于返回值的自动推导
            auto x1 = [](int i) { return i; };  // OK: return type is int
            //  auto x2 = [](){ return { 1, 2 }; };  // error: 无法推导出返回值类型
            /// lambda
            /// 表达式在没有参数列表时，参数列表是可以省略的。因此像下面的写法都是正确的：
            auto y1 = []() { return 1; };
            auto y2 = [] { return 1; };  // 省略空参数表
            std::cout << " - x1(0): " << x1(0) << std::endl;
            std::cout << " - y1: " << y1 << std::endl;
            std::cout << " - y2: " << y2 << std::endl;
        }
    };

    Simple::func();
    class Example {
        /// lambda 表达式的捕获列表精细地控制了 lambda
        /// 表达式能够访问的外部变量，以及如何访问这些变量。
     public:
        int i_ = 0;

        void func(int x, int y) {
            //      auto x1 = [] { return i_; };                    //
            //      error，没有捕获外部变量
            auto x2 = [&] { return i_ + x + y; };  // OK，捕获所有外部变量 c++20弃用 [=]
            auto x3 = [&] { return i_ + x + y; };  // OK，捕获所有外部变量
            auto x4 = [this] { return i_; };       // OK，捕获this指针
            //      auto x5 = [this] { return i_ + x + y; };        // error，没有捕获x、y
            auto x6 = [this, x, y] { return i_ + x + y; };  // OK，捕获this指针、x、y
            auto x7 = [this] { return i_++; };  // OK，捕获this指针，并修改成员的值
            std::cout << "Example\n -x2 -> " << x2() << std::endl
                      << " -x4 -> " << x4() << std::endl;
        }
    };
    //  Example::func()
    Example ex;
    ex.i_ = 2;
    ex.func(3, 4);
    int a = 0, b = 1;
    //  auto f1 = [] { return a; };               // error，没有捕获外部变量
    auto f2 = [&] { return a++; };  // OK，捕获所有外部变量，并对a执行自加运算
    auto f3 = [=] { return a; };  // OK，捕获所有外部变量，并返回a
    //  auto f4 = [=] { return a++; };            // error，a是以复制方式捕获的，无法修改
    //  auto f5 = [a] { return a + b; };          // error，没有捕获变量b
    auto f6 = [a, &b] { return a + (b++); };  // OK，捕获a和b的引用，并对b做自加运算
    auto f7 = [=, &b] {
        return a + (b++);
    };  // OK，捕获所有外部变量和b的引用，并对b做自加运算
    /// 默认状态下 lambda
    /// 表达式无法修改通过复制方式捕获的外部变量。如果希望修改这些变量的话，我们需要使用引用方式进行捕获。

    //// 关于 lambda 表达式的延迟调用的
    class B {
     public:
        static void func() {
            int a = 0;
            auto f = [=] { return a; };     /// 按值捕获外部变量
            a += 1;                         /// a被修改了 ？当然没有
            std::cout << f() << std::endl;  /// 输出？
            /// lambda 表达式按值捕获了所有外部变量。在捕获的一瞬间，a
            /// 的值就已经被复制到f中了。之后 a 被修改，但此时 f 中存储的 a
            /// 仍然还是捕获时的值，因此，最终输出结果是 0。 希望 lambda
            /// 表达式在调用时能够即时访问外部变量，我们应当使用引用方式捕获。
            auto f2 = [&] { return a; };
            a += 1;
            std::cout << f2() << std::endl;
        }
    };
    B::func();
    /// WARNING 被 mutable 修饰的 lambda 表达式就算没有参数也要写明参数列表

    /// 闭包类型 Closure Type
    class Type {
     public:
        /// 可以认为它是一个带有 operator() 的类，即仿函数。因此，我们可以使用 function 和
        /// bind 来存储和操作 lambda 表达式：
        std::function<int(int)> f1 = [](int a) { return a; };

        std::function<int(void)> f2 = std::bind([](int a) { return a; }, 123);
        /// 另外，对于没有捕获任何变量的 lambda 表达式，还可以被转换成一个普通的函数指针：
        using func_t = int (*)(int);

        func_t f = [](int a) { return a; };
    };
    Type Type;
    std::cout << "Type f -> " << Type.f(123) << std::endl;

    typedef void (*Ptr)(int*);
    Ptr p = [](int* p) {
        delete p;
    };  // 正确，没有状态的lambda（没有捕获）的lambda表达式可以直接转换为函数指针
    //  Ptr p1 = [&](int* p){delete p;};  // 错误，有状态的lambda不能直接转换为函数指针
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    int even_count = 0;
    /// change to Lambda before
    class CountEven {
        int& count_;

     public:
        explicit CountEven(int& count) : count_(count) {}

        void operator()(int val) {
            if (!(val & 1)) {
                ++count_;
            }
        }
    };
    for_each(v.begin(), v.end(), CountEven(even_count));
    std::cout << "The number of even is " << even_count << std::endl;
    /// change to lambda
    even_count = 0;
    for_each(v.begin(), v.end(), [&even_count](int val) {
        if (!(val & 1)) {  /// value % 2 == 0
            ++even_count;
        }
    });
    std::cout << "The number of even is " << even_count << std::endl;
    //  sort(v.begin(), v.end(), [=](int a, int b) {
    //    return b - a;
    //  });
    sort(v.rbegin(), v.rend());
    for (auto i : v) {
        std::cout << i << std::endl;
    }
}

// 值捕获
void lambda_value_capture() {
    // 与参数传值类似，值捕获的前提是变量可以拷贝，不同之处则在于，被捕获的变量在 Lambda
    // 表达式被创建时拷贝， 而非调用时才拷贝：
    int value = 1;
    auto copy_value = [value] { return value; };
    value = 100;
    auto stored_value = copy_value();
    augus::PrintTest("lambda_value_capture stored_value", stored_value);
}

// 引用捕获
void lambda_reference_capture() {
    int value = 1;
    auto copy_value = [&value] { return value; };
    value = 100;
    auto stored_value = copy_value();
    augus::PrintTest("lambda_reference_capture stored_value", stored_value);
}

// 表达式捕获
void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    // important 是一个独占指针，是不能够被
    // "=" 值捕获到，这时候我们可以将其转移为右值，在表达式中初始化。
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) {
        return x + y + v1 + (*v2);
    };
    augus::PrintTest("lambda_expression_capture add(3,4)", add(3, 4));
}

auto add = [](auto x, auto y) { return x + y; };

}  // namespace lambda_learning

using foo = void(int);
// 定义在参数列表中的函数类型 foo 被视为退化后的函数指针类型 foo*
void functional(foo f) {
    // 通过函数指针调用函
    f(1);
}

void functional_test() {
    auto f = [](int value) { augus::PrintTest("value", value); };
    functional(f);  // 传递闭包对象，隐式转换为 foo* 类型的函数指针值
    f(1);           // lambda 表达式调
}

int foo_func_int(int para) { return para; }

int func_case() {
    std::function<int(int)> func = foo_func_int;
    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1 + value + important;
    };
    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;

    return 0;
}

int foo_func_bind(int a, int b, int c) {
    ;
    return 0;
}

int func_bind_case() {
    // 将参数1,2绑定到函数 foo 上，但是使用 std::placeholders::_1 来对第一个参数进行占位
    auto bind_foo = std::bind(foo_func_bind, std::placeholders::_1, 3, 4);
    bind_foo(2);
    return 0;
}

void reference(std::string& str) { augus::PrintTest("l value", str); }

void reference(std::string&& str) { augus::PrintTest("r value", str); }

void reference(int& v) { augus::PrintTest("l value int", v); }

void reference(int&& v) { augus::PrintTest("r value int", v); }

// TODO 完美转发 还没看

void reference_case() {
    std::string lv1 = "str";
    // std::move可以将左值转移为右值
    std::string&& rv1 = std::move(lv1);
    augus::PrintTest("rv1", rv1);
    // 常量左值引用能够延长临时变量的生命周期
    const std::string& lv2 = lv1 + lv1;
    augus::PrintTest("lv2", lv2);
    std::string&& rv2 = lv1 + lv2;
    rv2 += "case";
    augus::PrintTest("rv2", rv2);
    reference(rv2);
}

class LReference {
 public:
    int* pointer;
    LReference() : pointer(new int(1)) { augus::PrintTest("construct", pointer); }
    LReference(LReference& lr) : pointer(new int(*lr.pointer)) {
        augus::PrintTest("copy but no sense", pointer);
    }
    LReference(LReference&& lr) noexcept : pointer(lr.pointer) {
        lr.pointer = nullptr;
        augus::PrintTest("move", pointer);
    }
    ~LReference() {
        augus::PrintTest("destruct", pointer);
        delete pointer;
    }
};

// 防止编译器优化
LReference return_rvalue(bool test) {
    LReference l1, l2;
    // 等价于 static_cast<A&&>(a);
    if (test)
        return l1;
    // 等价于 static_cast<A&&>(b)
    else
        return l2;
}

void vector_copy() {
    std::string str = "Hello World";
    std::vector<std::string> v;
    v.push_back(str);
    augus::PrintTest("str: ", str);
    v.push_back(std::move(str));
    augus::PrintTest("str: ", str);

    // vec 被清空元素的内存不会归还 shrink_to_fit 才可以
    v.shrink_to_fit();
}

void simple_arr(int* p, int len) {
    for (int i = 0; i < len; ++i) {
        std::cout << " " << p[i];
    }
    std::cout << std::endl;
}

void map_compare_unordered_map() {
    std::unordered_map<int, std::string> u = {{1, "1"}, {3, "3"}, {2, "2"}};
    std::map<int, std::string> v = {{1, "1"}, {3, "3"}, {2, "2"}};
    augus::PrintTest("std::unordered_map", "");
    for (const auto& n : u) {
        augus::PrintTest("key:[", n.first, "] value:[", n.second, "]");
    }
    augus::PrintTest("std::map", "");
    for (const auto& n : v) {
        augus::PrintTest("key:[", n.first, "] value:[", n.second, "]");
    }
}

// --------------------------------------------------------------------------------------
// solve 运行期索引
template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if constexpr (n >= sizeof...(T))
        throw std::out_of_range("out of range.");
    if (i == n)
        return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
    return _tuple_index<(n < sizeof...(T) - 1 ? n + 1 : 0)>(tpl, i);
}
template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}
template <typename T0, typename... Ts>
std::ostream& operator<<(std::ostream& s, std::variant<T0, Ts...> const& v) {
    std::visit([&](auto&& x) { s << x; }, v);
    return s;
}
// --------------------------------------------------------------------------------------

auto get_student(int id) {
    switch (id) {
        case 0:
            return std::make_tuple(3.9, 'A', "Paul");
        case 1:
            return std::make_tuple(2.8, 'B', "Meira");
        case 3:
            return std::make_tuple(1.7, 'C', "Ben");
        default:
            return std::make_tuple(0.0, 'D', "null");
    }
    return std::make_tuple(0.0, 'D', "null");
}

void use_tuple() {
    auto student = get_student(0);
    augus::PrintTest("ID: 0, GPA: ", std::get<0>(student),
                     ", rank: ", std::get<1>(student), ", name: ", std::get<2>(student));
    // 拆包
    double gpa;
    char rank;
    std::string name;
    std::tie(gpa, rank, name) = get_student(1);
    augus::PrintTest("ID: 1, GPA: ", gpa, ", rank: ", rank, ", name: ", name);

    auto cat_tuple = std::tuple_cat(get_student(1), std::move(student));
    for (int i = 0; i != augus::tuple_len(cat_tuple); ++i) {
        std::cout << tuple_index(cat_tuple, i) << std::endl;
    }

    // c++14 latter
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    // 依赖一个编译期的常量 解决方案见运行期索引
    // augus::PrintTest("get type",std::get<std::string>(student));
    augus::PrintTest("get type", std::get<std::string>(t));
}

// Custom Literal
std::string operator"" _wow(const char* wow1, size_t len) {
    return std::string(wow1) + "wow, amazing";
}

std::string operator"" _wow(unsigned long long i) {
    return std::to_string(i) + "wow, amazing";
}

struct Storage {
    char a;
    int b;
    double c;
    long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
    char a;
    int b;
    double c;
    long long d;
};

int main() {
    auto t0 = std::chrono::system_clock::now();

    augus::PrintTest("alignof(Storage): ",alignof(Storage));
    augus::PrintTest("alignof(AlignasStorage): ",alignof(AlignasStorage));

    use_tuple();

    map_compare_unordered_map();

    std::array<int, 4> simple_arr_values = {1, 2, 3, 4};
    simple_arr(simple_arr_values.data(), simple_arr_values.size());
    simple_arr(&simple_arr_values[0], simple_arr_values.size());

    vector_copy();

    LReference lr_boj = return_rvalue(false);
    augus::PrintTest("lr_obj", lr_boj.pointer, *lr_boj.pointer);

    reference_case();

    func_bind_case();

    func_case();

    functional_test();

    lambda_learning::lambda_value_capture();
    lambda_learning::lambda_reference_capture();
    lambda_learning::lambda_expression_capture();

    augus::PrintTest("new_enum value2", new_enum::value2);

    std::map<std::string, long long int> m{{"a", 1}, {"b", 2}, {"c", 3}};
    update(m, [](const std::string& key) -> long long int {
        return std::hash<std::string>{}(key);
    });
    for (auto&& [key, value] : m) std::cout << key << ":" << value << std::endl;

    SubBase sb(3);
    std::cout << sb.value1 << std::endl;
    std::cout << sb.value2 << std::endl;

    MagicFoo magic_foo = {1, 2, 3, 4, 5};
    std::cout << "magic foo:";
    for (auto it : magic_foo.vec) {
        std::cout << it << ", ";
    }
    std::cout << std::endl;

    TruelyDarkMagic<bool> you;

    U u{};
    int xu = u.i;
    char* pu = u.p;

    std::optional<int> optional_int = 6;
    std::variant<int, std::string> variant_ = 6;
    std::any any_ = 6;

    // 对 optional 解引用 解
    auto x1 = *optional_int;
    // 像访问 tuple 一样访问 variant
    auto x2 = std::get<int>(variant_);
    // 转换 any
    auto x3 = std::any_cast<int>(any_);

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

#ifdef WIN_CLION
    comp(vec_d_x1, vec_d_x2, vec_d_x3);
    user(int{99});
    std::cout << "fucky";
#endif

    //    augus::PrintTest(comp4(vec_d_x));

    std::promise<double> p_d;
    ff(2, p_d);



    LengthInKM marks[] = {LengthInMile(2.3), LengthInMile(0.76)};

    std::vector<var_t> vec_var_t = {10, 20L, 30.40, "hello"};
    for (auto& var : vec_var_t) {
        std::visit(overloaded{[](auto arg) { std::cout << arg << '\n'; },
                              [](double arg) { std::cout << "double:" << arg << '\n'; },
                              [](const std::string& arg) {
                                  std::cout << "\"" << arg << "\"\n";
                              }},
                   var);
    }

    auto t1 = std::chrono::system_clock::now();
    // duration_cast 把依赖于时钟的“嘀嗒”节拍数转换为程序员选用的时间单位
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
              << "msec\n";
    // c++20 可以直接使用 t1-t0

    return 0;
}