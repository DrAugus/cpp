// 米转换为尺寸

#include <stdio.h>

int main() {
  const double FT2M = 0.3048;
  int cm;
  scanf("%d", &cm);
  double meter = cm / 100.0;
  double inches = meter / FT2M;
  printf("%lf\n", inches);
  int foot, inch;
  foot = inches;
  inch = (inches - foot) * 12;
  printf("%d %d", foot, inch);
  return 0;
}