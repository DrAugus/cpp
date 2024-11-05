#include <stdio.h>
#include <string.h>

int main() {
  while (1) {
    char s[100];
    scanf("%s", s);
    size_t len = strlen(s);
    if (len == 0 || (len == 1 && s[0] == '.')) {
      break;
    }

    if (s[len - 1] == '.') {
      printf("%d", len - 1);
      break;
    } else {
      printf("%d ", len);
    }
  }

  return 0;
}