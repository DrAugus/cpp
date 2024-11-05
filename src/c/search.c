#include <stdio.h>

int search(int key, int a[], int len) {
  int ret = -1;
  for (int i = 0; i < len; i++) {
    if (a[i] == key) {
      ret = i;
      break;
    }
  }
  return ret;
}

int bin_search(int key, int a[], int len) {
  int left = 0;
  int right = len - 1;
  
  int ret = -1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (a[mid] < key) {
      left = mid +1;
    } else if (a[mid] > key) {
      right = mid -1;
    } else {
      ret = mid;
      break;
    } 
  }
  return ret;
}

int search_coin() {
  int amount[] = {1, 5, 10, 25, 50};
  char* name[] = {"penny", "nickel", "dime", "quarter", "half-dollar"};
  int key = 5;
  int r = search(key, amount, sizeof(amount) / sizeof(amount[0]));
  if (r > -1) {
    printf("%s", name[r]);
  }
  printf("\n");

  struct {
    int amount;
    char* name;
  } coins[] = {{1, "penny"},
               {5, "nickel"},
               {10, "dime"},
               {25, "quarter"},
               {50, "half-dollar"}};
  for (int i = 0; i < sizeof(coins) / sizeof(coins[0]); i++) {
    if (key == coins[i].amount) {
      printf("%s", coins[i].name);
      break;
    }
  }
  printf("\n");

  return 0;
}

int main() {
  //   search_coin();
  int a[] = {2, 3, 4, 5,6,8,11,25};
  int r = bin_search(3, a, sizeof(a) / sizeof(a[0]));
  printf("%d", r);
  return 0;
}