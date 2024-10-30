// 华氏转摄氏

#include <stdio.h>

int main() {
  int F;
  scanf("%d", &F);
  int C = 5 * (F - 32) / 9;

  printf("Celsius = %d\n", C);

  return 0;
}