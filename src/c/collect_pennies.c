// 对数字求特征值是常用的编码算法，奇偶特征是一种简单的特征值。
#include <stdio.h>
int main() {
  int n;
  // scanf("%d", &n);
  n = 2;
  for (int one = 1; one < 10 * n; one++) {
    for (int two = 0; two < 10 * n / 2; two++) {
      for (int five = 0; five < 10 * n / 5; five++) {
        if (one + two * 2 + five * 5 == n * 10) {
          printf("可以用%d个一角%d个贰角%d个五角得到%d元", one, two, five, n);
          goto out;
        }
      }
    }
  }
out:
  return 0;
}