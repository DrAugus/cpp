// cal log2x

#include <stdio.h>

int main() {
  int x;

  x = 64;
  int t = x;
  int ret = 0;  // 加法计算初始值 0 乘法计算初始值 1
  while (x > 1) {
    x /= 2;
    ret++;
  }
  printf("log2 of %d is %d", t, ret);
  return 0;
}