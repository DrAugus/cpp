#include <stdio.h>

int main() {
  int sum = 0, count = 0;
  int number;

  scanf("%d", &number);
  while (number != -1) {
    sum += number;
    count++;
    scanf("%d", &number);
  }

  printf("avg is %f", 1.0 * sum / count);
  return 0;
}