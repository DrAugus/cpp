// 分而治之

#include <meow.h>

int sum(int A[], int lo, int hi) {
  if (lo == hi)
    return A[lo];
  int mi = (lo + hi) >> 1;
  return sum(A, lo, mi) + sum(A, mi + 1, hi);
}

int sum(int A[], int n) {
  return (n < 1) ? 0 : sum(A, n - 1) + A[n - 1];
}

int main() {
  int A[] = {1, 2, 3, 4, 5, 6, 7};
  std::cout << sum(A, 0, sizeof(A) / sizeof(int));
  return 0;
}