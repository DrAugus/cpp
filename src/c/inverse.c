// 三位数逆序

#include <stdio.h>

int three_digit() {
  int input;
  scanf("%d", &input);
  int a, b, c;
  a = input / 100;
  c = input % 10;
  b = input / 10 % 10;
  printf("%d\n", c * 100 + b * 10 + a);
  return 0;
}

int reverse() {
  int x;
  // scanf("%d", &x);
  x = 123456;

  int ret = 0;
  int digit;

  while (x > 0) {
    digit = x % 10;
    // printf("%d", digit);
    ret = ret * 10 + digit;
    printf("x=%d,digit=%d,ret=%d\n", x, digit, ret);
    x /= 10;
  }
  printf("ret is %d\n", ret);
  return 0;
}

int main() {
  reverse();
  return 0;
}