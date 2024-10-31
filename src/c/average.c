#include <stdio.h>

int use_array() {
  double sum = 0.0;
  int count = 0;
  int x;
  int number[100];
  scanf("%d", &x);
  while (x != -1) {
    number[count] = x;
    sum += x;
    count++;
    scanf("%d", &x);
  }
  if (count > 0) {
    printf("avg is %f\n", sum / count);
    for (int i = 0; i < count; i++) {
      if (number[i] > sum / count) {
        printf("%d ", number[i]);
      }
    }
  }
  printf("\n");

  return 0;
}

int main() {
  use_array();
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