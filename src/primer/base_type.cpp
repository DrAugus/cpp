//
// base_type.cpp
// Created by AUGUS on 2022/9/25.
// 各种基本类型
//

#include <meow.h>

int main() {
    int iv = 1023;
    int &ref_iv = iv;
    iv = 2;
    ref_iv = 3;
    int &ref2 = ref_iv;
    int *p_iv = &ref_iv;
    *p_iv = 23;

    fmt::print("iv: {} {} {} {}\n", ref_iv, iv, ref2, *p_iv);

    int ti = 1024, *p_ti = &ti, &r_ti = ti;
    fmt::print("ti: {} {} {}\n", ti, *p_ti, r_ti);

    return 1;
}