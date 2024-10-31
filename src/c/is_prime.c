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

int get_prime2(int n, int m) {
  int x;
  int cnt = 0;
  x = n;
  // for (x = 2; x < 100; x++)
  while (cnt < m) {
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

int is_prime(int n) {
  int isPrime = 1;
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      isPrime = 0;
      break;
    }
  }
  return isPrime;
}

int get_prime3(int n, int m) {
  int x = 2;
  int cnt = 0;
  int sum = 0;
  while (cnt < m) {
    int isPrime = 1;
    for (int i = 2; i < x; i++) {
      if (x % i == 0) {
        isPrime = 0;
        break;
      }
    }
    if (isPrime == 1) {
      // printf("%d ", x);
      cnt++;
      if (cnt >= n && cnt <= m) {
        sum += x;
      }
      printf("x=%d,cnt=%d,sum=%d\n", x, cnt, sum);
    }
    x++;
  }
  printf("%d\n", sum);
  return 0;
}

int main() {
  // get_prime();

  // get_prime2(2, 4);

  get_prime3(4, 8);

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