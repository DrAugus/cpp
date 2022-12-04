#include <meow.h>
#ifdef __linux__
#include <arpa/inet.h>
#endif

class aa
{
public:
    aa(int a, std::string s) : a_(a), s_(s)
    {
        fmt::print("a [{}] s [{}] a_{} s_{}\n", a, s, a_, s_);
    }

    ~aa() {}

private:
    int a_;
    std::string s_;
};

typedef struct test
{
    test() : a(9), b(3)
    {
    }

    int a;
    int b;
    int c;
    int d;
} test_t;

void ss(test_t *t)
{
    int c = t->c;
    const test_t &a = t[0];
    int b = a.b;
}

int main()
{
    test ttt;
    ttt.c = 4;
    ttt.d = 8;

    ss(&ttt);

    aa aaa(3, "fuck");

    std::map<int, std::string> mm = {
        {1, "ss1"},
        {2, "ss3"}};
    std::vector<int> vv = {1, 2, 3, 4, 5, 2, 3, 3, 3, 2};
    auto euq = mm.equal_range(1);
    fmt::print("ti ,,, {}\n", euq.first->second);

    const std::string &raw_data = "33ffwfw";
    int64_t offset = 2;
    
#ifdef __linux__
    int ret = *(int *)(&raw_data[offset]);
    fmt::print("off:{}\n", ntohl(ret));
#endif

    double a = 2.3;
    fmt::print("double:{}\n", a * 4.5);

    printf("%f", a);

    return 0;
}
