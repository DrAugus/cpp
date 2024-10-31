// greatest common divisor 最大公约数
#include <stdio.h>

int normal() {
  int a, b;
  scanf("%d %d", &a, &b);
  int min = a < b ? a : b;
  int ret = 0;
  for (int i = 1; i <= min; i++) {
    if (a % i == 0 && b % i == 0) {
      ret = i;
    }
    printf("i=%d,ret=%d\n", i,ret);
  }
  printf("%d和%d的最大公约数是%d\n", a, b, ret);

  return 0;
}

// 辗转相除法
// 如果b等于0，计算结束，a就是最大公约数
// 否则，计算a除以b的余数，让a等于b，而b等于那个余数
// 回到第一步
int main() {
  normal();

  int a, b;
  int t;
  scanf("%d %d", &a, &b);
  while (b != 0) {
    t = a % b;
    a = b;
    b = t;
  }
  printf("gcd=%d\n", a);
  return 0;
}