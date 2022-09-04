//
// Created by AUGUS on 2022/9/4.
// 编写程序，定义 Ship 和 AirPlane 两个类
// 二者都有重量属性，定义二者的友元函数 CompareWeight 和 TotalWeight 分别比较两者大小及总重量和
//

#include <iostream>

class Ship;

class AirPlane;

class Ship {
private:
    double weight;
public:
    Ship(double w) { weight = w; }

    friend void CompareWeight(Ship &, AirPlane &);

    friend double TotalWeight(Ship &, AirPlane &);
};

class AirPlane {
private:
    double weight;
public:
    AirPlane(double w) { weight = w; }

    friend void CompareWeight(Ship &, AirPlane &);

    friend double TotalWeight(Ship &, AirPlane &);
};

void CompareWeight(Ship &s, AirPlane &a) {
    if (s.weight > a.weight) std::cout << "Ship's weight is heavy\n";
    else if (s.weight < a.weight) std::cout << "AirPlane's weight is heavy\n";
    else std::cout << "Both weigh the same\n";
}

double TotalWeight(Ship &s, AirPlane &a) {
    return s.weight + a.weight;
}

int main() {
    Ship s(2);
    AirPlane a(3.2);
    CompareWeight(s, a);
    std::cout << "TOTAL: " << TotalWeight(s, a) << std::endl;
    return 0;
}