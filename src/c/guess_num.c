#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(0));
  int number = rand() % 100 + 1;
  int count = 0;
  int a;
  printf("我已经想好了一个1到100的整数。");
  do {
    printf("请猜这个1到100的整数：");
    scanf("%d", &a);
    count++;
    if (a < number) {
      printf("你猜的数小了。");
    } else if (a > number) {
      printf("你猜的数大了。");
    }
  } while (a != number);

  printf("太厉害了，你用了%d次就猜到了答案。\n", count);
}