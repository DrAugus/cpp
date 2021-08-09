//
// Created by AUGUS on 2021/5/31.
//

#include "store_manage.hh"

#include "gtest/gtest.h"

int main(int argc, char *argv[])
{

//    testp();
    store_manage();

    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    return ret;
}