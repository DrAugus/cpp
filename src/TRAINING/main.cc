//
// Created by AUGUS on 2021/5/31.
//

#include "for_training.hh"
#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    op_list::commonOP();

    return ret;
}