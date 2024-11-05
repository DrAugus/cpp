#include <stdio.h>
#include <string.h>

int main() {
  // int n, m;
  // scanf("%d %d", &n, &m);

  char *p = "Hello";
  char *p2 = "Hello";
  printf("%d\n", p == p2);
  char p3[] = "Hello";
  char p4[] = "Hello";
  printf("%d\n", p3 == p4);

  char s1[] = "abc";
  char s2[] = "adc";
  printf("%d\n", strcmp(s1, s2));

  int a[] = {
      3, 4, 5, 6, 7, 8, 9,
  };
  int *pa = &a[5];
  printf("%d", pa[-2]);

  return 0;
}