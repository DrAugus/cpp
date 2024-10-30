#include <stdio.h>

int get_prime() {
  int x;
  int cnt = 0;
  x = 2;
  // for (x = 2; x < 100; x++)
  while (cnt < 50) {
    int isPrime = 1;
    for (int i = 2; i < x; i++) {
      if (x % i == 0) {
        isPrime = 0;
        break;
      }
    }
    if (isPrime == 1) {
      printf("%d ", x);
      cnt++;
    }
    x++;
  }
  printf("\n");
  return 0;
}

int main() {
  get_prime();

  int n;
  scanf("%d", &n);
  int isPrime = 1;
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      isPrime = 0;
      break;
    }
  }
  if (isPrime == 1) {
    printf("是素数");
  } else {
    printf("不是素数");
  }

  return 0;
}