// 多项式加法

#include <stdio.h>

int main() {
  // Power, coefficient 幂次、系数
  const int MAX_POWER = 101;
  int poly[MAX_POWER];
  int power, coefficient;

  // init
  for (int j = 0; j < MAX_POWER; j++) {
    poly[j] = 0;
  }

  // input
  for (int i = 0; i < 2; i++) {
    do {
      scanf("%d %d", &power, &coefficient);
      poly[power] += coefficient;
    } while (power != 0);
  }

  int flag = 1;
  for (int i = MAX_POWER - 1; i >= 0; i--) {
    if (poly[i]) {
      if (!flag && poly[i] > 0) {
        printf("+");
      }
      if (i == 0 || poly[i] != 1 && poly[i] != -1) {
        printf("%d", poly[i]);
      } else if (poly[i] == -1) {
        printf("-");
      }

      if (i > 0) {
        printf("x");
        if (i > 1) printf("%d", i);
      }
      flag = 0;
    }
  }
  if (flag) {
    printf("0");
  }

  printf("\n");

  return 0;
}