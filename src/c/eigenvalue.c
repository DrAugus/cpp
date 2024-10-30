// 对数字求特征值是常用的编码算法，奇偶特征是一种简单的特征值。
#include <stdio.h>
int main() {
  int n;
  scanf("%d", &n);
  int digital, count = 0, ret = 0;
  int bin = 1;
  while (n > 0) {
    digital = n % 10;
    count++;
    int compare = (digital % 2) == (count % 2);
    bin *= 2;
    ret += compare * (bin / 2);
    // printf("digital=%d,count=%d,com=%d,ret=%d,bin=%d\n", digital, count,
    //        compare, ret, bin);
    n /= 10;
  }

  printf("%d", ret);

  return 0;
}