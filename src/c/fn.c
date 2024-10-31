#include <stdio.h>

// fn = 1 + 1/2 + 1/3 +...+ 1/n
int fn() {
  int n;
  scanf("%d", &n);

  int i;
  double sum = 0.0;

  for (i = 1; i < n; i++) {
    sum += 1.0 / i;
  }
  printf("f(%d)=%f\n", n, sum);
  return 0;
}

// fn = 1 - 1/2 + 1/3 - 1/4 +...+ 1/n
int fn2() {
  int n;
  scanf("%d", &n);

  int i;
  int sign = 1;
  double sum = 0.0;

  for (i = 1; i < n; i++) {
    sum += sign * 1.0 / i;
    sign = -sign;
  }
  printf("f(%d)=%f\n", n, sum);

  return 0;
}

int main() {
  fn2();
  return 0;
}