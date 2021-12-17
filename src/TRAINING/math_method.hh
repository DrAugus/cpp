//
// Created by AUGUS on 2021/7/1.
//

#ifndef AUGUSTEST_MATH_METHOD_HH
#define AUGUSTEST_MATH_METHOD_HH

#include <memory>
#include <cmath>
#include <random>
#include <iostream>

#include "augus/augus.h"

class math_method;

using math_method_sptr = std::shared_ptr<math_method>;

class math_method:
    public std::enable_shared_from_this<math_method>
{
public:
    math_method() = default;
    virtual ~math_method() = default;
    math_method(const math_method &) = delete;
    math_method &operator=(const math_method &) = delete;
public:
    static math_method_sptr instance();
public:
    //最大公约数
    int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
    void getRand();
};//class math_method


namespace math_case {
class Point
{
protected:
    double x;
    double y;
public:
    Point() : x(0), y(0) {};
    Point(double a, double b) : x(a), y(b) {};
    double getX() const { return x; }
    double getY() const { return y; }
};//class Point

class CalAngle: Point
{
public:
    double XAngel(Point p1, Point p2)
    {
        auto angle = atan2((p2.getY() - p1.getY()), (p2.getX() - p1.getX())); ///弧度
        return angle;
    }

    double XTheta(Point p1, Point p2)
    {
        auto angle = XAngel(p1, p2);
        auto theta = angle * (180 / M_PI); ///角度
        return theta;
    }

/// CCW counterclockwise
    double XAngel(Point p1, Point p2, bool CCW)
    {
        auto angle = atan2((p1.getY() - p2.getY()), (p2.getX() - p1.getX())); ///弧度
        return angle;
    }

    double XTheta(Point p1, Point p2, bool CCW)
    {
        auto angle = XAngel(p1, p2, true);
        auto theta = angle * (180 / M_PI); ///角度
        return theta;
    }

    double YAngel(Point p1, Point p2)
    {
        auto angle = atan2((p2.getX() - p1.getX()), (p2.getY() - p1.getY())); ///弧度
        return angle;
    }

    double YTheta(Point p1, Point p2)
    {
        auto angle = XAngel(p1, p2);
        auto theta = angle * (180 / M_PI); ///角度
        return theta;
    }
};//class CalAngle



}//namespace math_case


#endif //AUGUSTEST_MATH_METHOD_HH
