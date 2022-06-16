//
// case2.cpp
// Created by AUGUS on 2022/6/16.
//

#include <iostream>

void declare() {
    int i;
    int a[100];
    for (i = 0; i < 100; i++) {
        a[i] = i;
    }
    for (i = 0; i < 100; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void print() {
    int i;
    int a[100];
    for (i = 0; i < 100; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    printf("=================\n");
    printf("memory\n");
    declare();
    print();

    printf("=================\n");
    declare();
    printf("now random\n");
    print();

    return 0;
}