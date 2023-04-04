#include <meow.h>

class Base
{
private:
    /* data */
    int i;

public:
    Base(/* args */) { std::cout << "Base constructor\n"; }
    virtual ~Base() { std::cout << "Base deconstructor\n"; };
};

class Extend : public Base
{
private:
    /* data */
    int i;
    int j;

public:
    Extend(/* args */) { std::cout << "Extend constructor\n"; }
    ~Extend() { std::cout << "Extend deconstructor\n"; }
};

int main()
{
    Base *ex = new Extend();
    std::cout << sizeof(Base) << " " << sizeof(Extend) << std::endl;
    delete ex;
    fmt::print("base size is {} extend size is {}\n", sizeof(Base), sizeof(Extend));

    return 0;
}
