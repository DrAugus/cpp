#include <stdio.h>

int max(int a[], int len) {
  int max_id = 0;
  for (int i = 1; i < len; i++) {
    if (a[i] > a[max_id]) {
      max_id = i;
    }
  }
  return max_id;
}

void sort1(int a[], int len) {
  for (int i = len - 1; i > 0; i--) {
    int max_id = max(a, i + 1);
    int t = a[max_id];
    a[max_id] = a[i];
    a[i] = t;
  }
}

int main() {
  int a[] = {2, 4, 5, 11, 3, 6, 9, 13};
  int len = sizeof(a) / sizeof(a[0]);
  sort1(a, len);
  for (int i = 0; i < len; i++) {
    printf("%d\t", a[i]);
  }
  printf("\n");
  return 0;
}