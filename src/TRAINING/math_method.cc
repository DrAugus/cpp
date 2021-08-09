//
// Created by AUGUS on 2021/7/1.
//

#include "math_method.hh"
#include "gtest/gtest.h"

math_method_sptr math_method::instance()
{
    static math_method_sptr _sptr = nullptr;
    if (_sptr == nullptr) {
        _sptr = std::make_shared<math_method>();
    }
    return _sptr;
}


TEST(math_method, gcd)
{
    auto p = math_method::instance();
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
void math_method::getRand()
{
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




