#include <stdio.h>

int main() {
  int i;
  for (i = 0; i < 5; i++) {
    printf("i = %d ", i);
  }
  printf("\nend i = %d\n", i);

  for (i = 1; i <= 5; i++) {
    printf("i = %d ", i);
  }
  printf("\nend i = %d\n", i);

  for (i = 0; i < 5; ++i) {
    printf("i = %d ", i);
  }
  printf("\nend i = %d\n", i);

  for (i = 1; i <= 5; ++i) {
    printf("i = %d ", i);
  }
  printf("\nend i = %d\n", i);

  return 0;
}