//
// uv_test.cpp
// Created by AUGUS on 2022/3/1.
//

#include <stdio.h>
#include <stdlib.h>

//尝试了单独新建c项目 可以编译通过

//TODO 解决编译失败

#include <uv.h>

int main() {
    auto *loop = (uv_loop_t *) malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
    return 0;
}

