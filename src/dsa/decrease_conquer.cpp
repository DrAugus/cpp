// 减而治之

#include <meow.h>

// 递归版
void reverse(int* A, int lo, int hi) {
  if (lo < hi) {
    std::swap(A[lo], A[hi]);
    reverse(A, lo + 1, hi - 1);
  }
}

//  迭代原始
void reverse1(int* A, int lo, int hi) {
next:
  if (lo < hi) {
    std::swap(A[lo], A[hi]);
    lo++;
    hi--;
    goto next;
  }
}

// 迭代精简
void reverse2(int* A, int lo, int hi) {
  while (lo < hi) {
    std::swap(A[lo++], A[hi--]);
  }
}

int main() {
  int A[] = {1, 3, 4, 5, 6, 7, 8, 3, 2};
  fmt::print("A {} \n", A);

  reverse(A, 0, sizeof(A) / sizeof(int) - 1);
  fmt::print("A {} \n", A);
  return 0;
}