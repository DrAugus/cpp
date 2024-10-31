#include <stdio.h>

int main() {
  int x;
  scanf("%d", &x);
  int count[10];

  while (x != -1) {
    if (x >= 0 && x <= 9) {
      count[x]++;
    }
    scanf("%d", &x);
  }
  for (int i = 0; i < 10; i++) {
    printf("%d:%d\n", i, count[i]);
  }
  return 0;
}