#include <stdio.h>

struct MyTime {
  int hour;
  int minute;
};
int minutes_diff(struct MyTime time1, struct MyTime time2) {
  int total_minutes1 = time1.hour * 60 + time1.minute;
  int total_minutes2 = time2.hour * 60 + time2.minute;
  return total_minutes2 - total_minutes1;
}
void time_diff(struct MyTime time1, struct MyTime time2, char* result,
               size_t buffer_size) {
  int ih = time2.hour - time1.hour;
  if (ih < 0) {
    snprintf(result, buffer_size, "TIME ERROR");
    return;
  }
  int im = time2.minute - time1.minute;
  if (im < 0) {
    im += 60;
    ih--;
  }
  if (ih == 0 && im == 0) {
    snprintf(result, buffer_size, "time equal");
    return;
  }

  if (ih == 0) {
    snprintf(result, buffer_size, "%d minutes", im);
    return;
  } else if (im == 0) {
    snprintf(result, buffer_size, "%d hours", ih);
    return;
  }

  snprintf(result, buffer_size, "%d hours and %d minutes", ih, im);
}

int main() {
  struct MyTime start = {9, 0};
  struct MyTime end = {10, 30};
  printf("输入前一个时间\n");
  scanf("%d %d", &start.hour, &start.minute);
  printf("输入后一个时间\n");
  scanf("%d %d", &end.hour, &end.minute);

  char buffer[100];  // 提供一个足够大的缓冲区来存储结果
  time_diff(start, end, buffer, sizeof(buffer));
  printf("Time difference: %s\n", buffer);

  return 0;
}