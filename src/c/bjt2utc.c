// BJT to UTC 北京时间转世界协调时

#include <stdio.h>

int main() {
  int bjt;
  scanf("%d", &bjt);

  int bjt_h, bjt_m;
  bjt_h = bjt / 100;
  bjt_m = bjt % 100;

  int utc;

  int utc_h, utc_m;
  utc_h = bjt_h - 8;
  utc_m = bjt_m;

  if (utc_h < 0) {
    utc_h += 24;
  }

  if (utc_h == 0) {
    utc = utc_m;
  } else {
    utc = utc_h * 100 + utc_m;
  }

  printf("%d\n", utc);

  return 0;
}