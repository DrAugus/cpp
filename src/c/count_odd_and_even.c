#include <stdio.h>
int main() {
  int n;
  scanf("%d", &n);
  int odd = 0, even = 0;
  while (n != -1) {
    if (n % 2) {
      odd++;
    } else {
      even++;
    }
    scanf("%d", &n);
  }

  printf("%d %d", odd, even);

  return 0;
}